/* Triangle.cpp */

#include "Triangle.h"

Triangle::Triangle(VecPoint a, VecPoint b, VecPoint c)
{
  if (a.getI() == 1 && b.getI() == 1 && c.getI() == 1) {
    this->v1 = a;
    this->v2 = b;
    this->v3 = c;
  }
  else {
    cout << "Triangle is made up of 3 points and no vectors\n";
    exit(EXIT_FAILURE);
  }
}

VecPoint Triangle::getCenter() {
  double x, y, z;
  x = (this->getV1().getX() + this->getV2().getX() + this->getV3().getX())/3;
  y = (this->getV1().getY() + this->getV2().getY() + this->getV3().getY())/3;
  z = (this->getV1().getZ() + this->getV2().getZ() + this->getV3().getZ())/3;
  VecPoint result = VecPoint(x,y,z,1);
  return result;
}

Color Triangle::shade_tri(VecPoint cam, VecPoint pos, Color kd, Color ks, double power, Light light) {
  VecPoint center = this->getCenter();
  Color diffuse_term = Color(0,0,0);
  Color specular_term = Color(0,0,0);
  Color result = Color(0,0,0);
  VecPoint light_xyz = VecPoint(light.getX(), light.getY(), light.getZ(), 1.0);
  Color light_rgb = Color(light.getR(), light.getG(), light.getB());

  VecPoint edge1 = this->getV2().subtract(this->getV1());
  VecPoint edge2 = this->getV3().subtract(this->getV1());

  VecPoint surface = edge1.crossProduct(edge2);
  VecPoint surface_normal = surface.normalize();

  VecPoint light_vec;

  if (light.isPointLight())
  {
    light_vec = light_xyz.subtract(pos);
  }
  else
  {
    light_vec = VecPoint(-light_xyz.getX(), -light_xyz.getY(), -light_xyz.getZ(), 0);
  }

  VecPoint light_normal = light_vec.normalize();
  double refl = light_normal.dotProduct(surface_normal) * 2;
  VecPoint comp1 = surface_normal.scale(refl);
  VecPoint r = comp1.subtract(light_normal);
  VecPoint reflectance = r.normalize();

  VecPoint view = cam.subtract(pos);
  VecPoint view_normal = view.normalize();

  double zero = 0;
  Color diff_color = Color(light_rgb.getR(), light_rgb.getG(), light_rgb.getB());
  Color spec_color = Color(light_rgb.getR(), light_rgb.getG(), light_rgb.getB());

  //diffuse term  
  double diff_scale = max(light_normal.dotProduct(surface_normal), zero);
  diff_color.colorScale(diff_scale);
  diff_color.colorMul(kd);
  diffuse_term.colorAdd(diff_color);
  
  //specular term
  double spec_scale = pow(max(view_normal.dotProduct(reflectance), zero), power);
  spec_color.colorScale(spec_scale);
  spec_color.colorMul(ks);
  specular_term.colorAdd(spec_color);

  result.colorAdd(diffuse_term);
  result.colorAdd(specular_term);
  return result;
}

void Triangle::display()
{
  cout << "v1: ";
  this->getV1().display();
  cout << "\n";
  cout << "v2: ";
  this->getV2().display();
  cout << "\n";
  cout << "v3: ";
  this->getV3().display();
  cout << "\n";
}