/* Sphere.h */

#ifndef SPHERE_H
#define SPHERE_H

#include <algorithm>
#include <iostream>     /* cout */
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* exit, EXIT_FAILURE */
#include "Color.h"
#include "VecPoint.h"
#include "Light.h"
using namespace std;

/* Representation of a spherical shape in the scene */

class Sphere
{
  private:
    double x, y, z, r;

  public:
    /* Constructor */
    Sphere() {}
    Sphere(double, double, double, double);

    /* Accessor functions */
    double getX() {return this->x;}
    double getY() {return this->y;}
    double getZ() {return this->z;}
    double getRadius() {return this->r;}

    /* Prints the sphere center and radius */
    void display();

    /** phong shading for point 
    camera, point on sphere, ka, kd coef, ks coef, power, light
    **/
    Color shade_point(VecPoint, VecPoint, Color, Color, double, Light);
};

#endif
