/* Triangle.h */

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <iostream>     /* cout */
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* exit, EXIT_FAILURE */
#include "VecPoint.h"
#include "Color.h"
#include "Light.h"
using namespace std;

/* Representation of a triangular shape in the scene */

class Triangle
{
  private:
    VecPoint v1, v2, v3;

  public:
    /* Constructor */
    Triangle() {}
    Triangle(VecPoint, VecPoint, VecPoint);

    /* Accessor functions */
    VecPoint getV1() {return this->v1;}
    VecPoint getV2() {return this->v2;}
    VecPoint getV3() {return this->v3;}

    VecPoint getCenter();

    Color shade_tri(VecPoint, VecPoint, Color, Color, double, Light);
    /* Prints the triangle vertices */
    void display();
};

#endif
