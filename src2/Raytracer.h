/* Raytracer.h */

#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <iostream>     /* cout */
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* exit, EXIT_FAILURE */
#include "Scene.h"

using namespace std;
/*
 * The Raytracer class will be used to compute the color for a generated ray.
 */

class Raytracer
{
  private:
    Scene scene;

  public:

    /** Constructor **/
    Raytracer(Scene sc) {this->scene = sc;}

    /** Accessor **/
    Scene getScene() {return this->scene;}

    /** Ray tracing **/
    Color trace(Ray, int, Color);

    /** sphere, min_index, closest_intersection, Ray, depth, Color **/
    Color trace_sphere(Sphere, int, VecPoint, Ray, int, Color);

    /** Triangle, min_index, closest_intersection, Ray, depth, Color **/
    Color trace_triangle(Triangle, int, VecPoint, Ray, int, Color);

};

#endif