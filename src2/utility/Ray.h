/* Ray.h */

#ifndef RAY_H
#define RAY_H

#include <iostream>     /* cout */
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* exit, EXIT_FAILURE */
#include "VecPoint.h"
#include "Triangle.h"
#include "Sphere.h"
using namespace std;

/* Representation of a ray to be used for raytracing.
 * Supports:
 * testing for intersection against triangle
 * testing for intersection against sphere
 */

class Ray
{
  private:
    VecPoint origin, vector;
    double tMin, tMax;
    Ray() {}

  public:
    /* Constructor */

    /*
     * Note: the first VecPoint passed in is the origin position,
     * the second is the ray direction vector
     */
    Ray(VecPoint, VecPoint);

    /* Accessor Functions */
    VecPoint getOrigin() {return this->origin;}
    VecPoint getVector() {return this->vector;}
    double getTMin() {return this->tMin;}
    double getTMax() {return this->tMax;}

    /* Intersection */
    VecPoint intersectTriangle(Triangle);
    VecPoint intersectSphere(Sphere);

    /* Prints the ray */
    void display();
};

#endif