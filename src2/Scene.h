/* Scene.h */

#ifndef SCENE_H
#define SCENE_H
#include "Film.h"
#include "lodepng.h"
#include "utility/VecPoint.h"
#include "utility/Color.h"
#include "utility/Light.h"
#include "utility/Triangle.h"
#include "utility/Sphere.h"
#include "utility/Ray.h"
#include <map>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <math.h>
using namespace std;


class Scene {
  //fill from the object file. in the main method, create a new scene, then have a scene method that parses and adds.
  private:
    VecPoint ll, lr, ul, ur; //image plane VecPoints
    VecPoint camera; //camera point
    vector<Light> lights; //lights
    map<int, Sphere> spheres;
    map<int, Triangle> triangles;
    Color ka_light; //ambient light color
    vector<Color> ka; //ambient coefficients
    vector<Color> kd; //diffuse coefficients
    vector<Color> ks; //specular coefficients
    vector<Color> kr; //reflective coefficients
    vector<double> sp; //shininess

  public:
    /** empty constructor **/
    Scene() {};

    /** scene with a file to populate **/
    Scene(ifstream &file);

    /** get ka_light **/
    Color getKaLight() {return this->ka_light;}

    /** get ka **/
    vector<Color> getKa() {return this->ka;}

    /** get kd **/
    vector<Color> getKd() {return this->kd;}

    /** get ks **/
    vector<Color> getKs() {return this->ks;}

    /** get sp **/
    vector<double> getSp() {return this->sp;}

    /** get kr **/
    vector<Color> getKr() {return this->kr;}

    /** set ka **/
    void setKa(vector<Color> v) {this->ka = v;}

    /** set kd **/
    void setKd(vector<Color> v) {this->kd = v;}

    /** set ks **/
    void setKs(vector<Color> v) {this->ks = v;}

    /** set kr **/
    void setKr(vector<Color> v) {this->kr = v;}

    /** set sp **/
    void setSp(vector<double> v) {this->sp = v;}

    /** get lower left **/
    VecPoint getLowerLeft() {return this->ll;}

    /** get lower right **/
    VecPoint getLowerRight() {return this->lr;}

    /** get upper left **/
    VecPoint getUpperLeft() {return this->ul;}

    /** get upper right **/
    VecPoint getUpperRight() {return this->ur;}

    /** get camera method **/
    VecPoint getCamera() {return this->camera;}

    /** set lower left **/
    void setLowerLeft(VecPoint v) {this->ll = v;}

    /** set lower right **/
    void setLowerRight(VecPoint v) {this->lr = v;}

    /** set upper left **/
    void setUpperLeft(VecPoint v) {this->ul = v;}

    /** set upper right **/
    void setUpperRight(VecPoint v) {this->ur = v;}

    /** set camera method **/
    void setCamera(VecPoint c) {this->camera = c;}

    /** set lights **/
    void setLights(vector<Light> l) {this->lights = l;}

    /** set triangles **/
    void setTriangles(map<int, Triangle> t) {this->triangles = t;}

    /** set spheres **/
    void setSpheres(map<int, Sphere> s) {this->spheres = s;}

    /** get light vector **/
    vector<Light> getLights() {return this->lights;}

    /** get triangles formed by scene **/
    map<int, Triangle> getTriangles() {return this->triangles;}

    /** get spheres formed by scene **/
    map<int, Sphere> getSpheres() {return this->spheres;}

    /** populate the scene **/
    void populate(ifstream &file);

    /** calculate p **/
    VecPoint calculateP(VecPoint, VecPoint, VecPoint, VecPoint, double, double);

    /** set up to output to file **/
    void setUp();

};

#endif




