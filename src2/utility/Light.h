/* Light.h */

#ifndef LIGHT_H
#define LIGHT_H

#include <iostream>     /* cout */
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* exit, EXIT_FAILURE */

using namespace std;

/* Representation of a light source */

class Light
{
  private:
    double x, y, z;
    double r, g, b;
    bool point;
    double fallOff;

  public:
    Light(double, double, double, double, double, double, double, bool);
            // x, y, z, r, g, b, fallOff, isPointLight
    double getX() {return this->x;}
    double getY() {return this->y;}
    double getZ() {return this->z;}
    double getR() {return this->r;}
    double getG() {return this->g;}
    double getB() {return this->b;}
    double getFallOff() {return this->fallOff;}
    double isPointLight() {return this->point;}
    void display();

};

#endif
