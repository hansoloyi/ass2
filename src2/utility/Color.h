/* Color.h */

#ifndef COLOR_H
#define COLOR_H

#include <iostream>     /* cout */
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* exit, EXIT_FAILURE */
using namespace std;

/* Representation of a color source 
 * Supports:
 * element-wise multiplication
 * element-wise addition
 * scaling
 */

class Color
{
  private:
    double r, g, b;

  public:
    /* Constructor */
    Color() {}
    Color(double, double, double);

    /* Prints this VecPoint */
    void display();

    /* Accessor functions */
    double getR() {return this->r;}
    double getG() {return this->g;}
    double getB() {return this->b;}

    void setR(double red) {this->r = red;}
    void setG(double green) {this->g = green;}
    void setB(double blue) {this->b = blue;}

    /* Element wise multiplication of two colors */
    void colorMul(Color);

    /* Element wise addition of two colors */
    void colorAdd(Color);

    /* Element wise subtraction of two colors */
    void colorSub(Color);

    /* Element wise scaling of this Color by a double */
    void colorScale(double);

};

#endif


