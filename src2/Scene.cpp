/* Scene.cpp */

#include "Scene.h"
#include "Raytracer.h"
using namespace std;

/** Constructor **/
Scene::Scene(ifstream &file) {
  populate(file);
}

/** populates the scene from a file **/ 
void Scene::populate(ifstream &file) {
  int map_index=0;
  string line;
  while(getline(file, line)) {
    string s;
    stringstream ss(line);
    vector<string> arguments;
    while(ss >> s) {
      arguments.push_back(s);
    }

    /** add a camera and image plane **/
    if (arguments.at(0).compare("cam") == 0) {
      VecPoint camera = VecPoint(stof(arguments.at(1)), stof(arguments.at(2)), stof(arguments.at(3)), 1.0);
      this->setCamera(camera);
      VecPoint lower_left = VecPoint(stof(arguments.at(4)), stof(arguments.at(5)), stof(arguments.at(6)), 1.0);
      VecPoint lower_right = VecPoint(stof(arguments.at(7)), stof(arguments.at(8)), stof(arguments.at(9)), 1.0);
      VecPoint upper_left = VecPoint(stof(arguments.at(10)), stof(arguments.at(11)), stof(arguments.at(12)), 1.0);
      VecPoint upper_right = VecPoint(stof(arguments.at(13)), stof(arguments.at(14)), stof(arguments.at(15)), 1.0);
      this->setLowerLeft(lower_left);
      this->setLowerRight(lower_right);
      this->setUpperLeft(upper_left);
      this->setUpperRight(upper_right);
    }

    /** add spheres to sphere vector **/
    else if (arguments.at(0).compare("sph") == 0) {
      Sphere sph = Sphere(stof(arguments.at(1)), stof(arguments.at(2)), stof(arguments.at(3)), stof(arguments.at(4)));
      this->spheres.insert(pair<int, Sphere>(map_index,sph));
      map_index++;
    }

    /** add triangles to triangle vector **/
    else if (arguments.at(0).compare("tri") == 0) {
      VecPoint a = VecPoint(stof(arguments.at(1)), stof(arguments.at(2)), stof(arguments.at(3)), 1);
      VecPoint b = VecPoint(stof(arguments.at(4)), stof(arguments.at(5)), stof(arguments.at(6)), 1);
      VecPoint c = VecPoint(stof(arguments.at(7)), stof(arguments.at(8)), stof(arguments.at(9)), 1);
      Triangle tr = Triangle(a,b,c);
      this->triangles.insert(pair<int, Triangle>(map_index,tr));
      map_index++;
    }

    /** add point light source to lights **/
    else if (arguments.at(0).compare("ltp") == 0) {
      if (arguments.size() == 7) {
        Light pl = Light(stof(arguments.at(1)), stof(arguments.at(2)), stof(arguments.at(3)), stof(arguments.at(4)), 
          stof(arguments.at(5)), stof(arguments.at(6)), 0.0, true);
        this->lights.push_back(pl);
      } else {
        Light pl = Light(stof(arguments.at(1)), stof(arguments.at(2)), stof(arguments.at(3)), stof(arguments.at(4)), 
          stof(arguments.at(5)), stof(arguments.at(6)), stof(arguments.at(7)), true);
        this->lights.push_back(pl);
      }
    }

    /** add directional light source to lights **/
    else if (arguments.at(0).compare("ltd") == 0) {
      Light dl = Light(stof(arguments.at(1)), stof(arguments.at(2)), stof(arguments.at(3)), stof(arguments.at(4)), 
          stof(arguments.at(5)), stof(arguments.at(6)), 0.0, false);
      this->lights.push_back(dl);
    }

    /** add objects based on obj file **/
    else if (arguments.at(0).compare("obj") == 0) {

    }

    /** an ambient light source **/
    else if (arguments.at(0).compare("lta") == 0) {
      this->ka_light.setR(stof(arguments.at(1)));
      this->ka_light.setG(stof(arguments.at(2)));
      this->ka_light.setB(stof(arguments.at(3)));
    }

    /** material **/
    else if (arguments.at(0).compare("mat") == 0) {
      /** ambient coefficients **/
      Color ka_val = Color(stof(arguments.at(1)), stof(arguments.at(2)), stof(arguments.at(3)));
      this->ka.push_back(ka_val);

      /** diffuse coefficients **/
      Color kd_val = Color(stof(arguments.at(4)), stof(arguments.at(5)), stof(arguments.at(6)));
      this->kd.push_back(kd_val);

      /** specular coefficients **/
      Color ks_val = Color(stof(arguments.at(7)), stof(arguments.at(8)), stof(arguments.at(9)));
      this->ks.push_back(ks_val);

      /** specular exponents **/
      double sp_val = stof(arguments.at(10));
      this->sp.push_back(sp_val);

      /** reflective coefficients **/
      Color kr_val = Color(stof(arguments.at(11)), stof(arguments.at(12)), stof(arguments.at(13)));
      this->kr.push_back(kr_val);

    }

    /** still need transformations **/

    /** exit if not right commands **/
    else {
      cout << "Please use correct commands\n";
      exit(EXIT_FAILURE);
    }
  }
}

VecPoint Scene::calculateP(VecPoint ll, VecPoint lr, VecPoint ul, VecPoint ur, double u, double v) {
  VecPoint a = lr.scaleForP(v);
  VecPoint b = ur.scaleForP(1-v);
  VecPoint k = a.addForP(b);
  VecPoint m = k.scaleForP(u);

  VecPoint c = ll.scaleForP(v);
  VecPoint d = ul.scaleForP(1-v);
  VecPoint l = c.addForP(d);
  VecPoint n = l.scaleForP(1-u);

  VecPoint result = m.addForP(n);
  return result;
}

void Scene::setUp() {
  Film f = Film();
  Raytracer rt = Raytracer(*this);
  f.setDimensions(this->getLowerLeft(), this->getLowerRight(), this->getUpperLeft(), this->getUpperRight());

  int width = f.getX();
  int height = f.getY();

  for (int j = 0; j < height; j++) {
    for (int i = 0; i < width; i++) {

      Color color_total = Color(0,0,0); // start off with black

      double u = (i + .5)/width; //u for getting p on image plane
      double v = (j + .5)/height; //v for getting p on image plane

      VecPoint p = this->calculateP(this->getLowerLeft(), this->getLowerRight(), \
        this->getUpperLeft(), this->getUpperRight(), u, v); //calculate p
      VecPoint d = p.subtract(this->getCamera());
      VecPoint direction = d.normalize();
      Ray r = Ray(this->getCamera(), direction); // ray through p
      Color c = rt.trace(r, 0, color_total);
      if (c.getR() > 1.0) {
        c.setR(1.0);
      }
      if (c.getG() > 1.0) {
        c.setG(1.0);
      }
      if (c.getB() > 1.0) {
        c.setB(1.0);
      }
      f.pixelate(c.getR(), c.getG(), c.getB());
    }
  }
  f.write();
}

