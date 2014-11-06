/* VecPoint.h */

#ifndef VECPOINT_H
#define VECPOINT_H

#include <iostream>     /* cout */
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* exit, EXIT_FAILURE */
#include <math.h>       /* pow */
using namespace std;

/* Representation of a point or vector. The field i can only be 0 or 1 
 * to denote vector and point respectively. If it's not, program will end.
 * Supports:
 * addition of 2 vectors -> vector
 * subtraction of 2 vectors -> vector
 * subtraction of vector from point = point (moving a point)
 * subtractions of point from point = vector (distance)
 */

class VecPoint
{
  private:
    double x, y, z, i;

  public:
    /* Constructors */
    VecPoint() {}
    VecPoint(double, double, double, double);

    /* Accessor functions */
    double getX() {return this->x;}
    double getY() {return this->y;}
    double getZ() {return this->z;}
    double getI() {return this->i;}

    void setI(double i) {this->i = i;}
    void setX(double x) {this->x = x;}
    void setY(double y) {this->y = y;}
    void setZ(double z) {this->z = z;}
    /* Prints this VecPoint */
    void display();

    /* Checks if this VecPoint is null */
    bool isEmpty();

    /* Element wise addition of a VecPoint and this VecPoint */
    VecPoint add(VecPoint);

    /** Element addition for calculating P **/
    VecPoint addForP(VecPoint);

    /** Element scale for calculating P **/
    VecPoint scaleForP(double);

    /* Element wise subtraction of a VecPoint from this VecPoint */
    VecPoint subtract(VecPoint);

    /* Element wise scaling of this VecPoint by a double */
    VecPoint scale(double);

    /* Normalization of a vector */
    VecPoint normalize();

    /** Dot Product of 2 VecPoints **/
    double dotProduct(VecPoint);

    /** Cross Product of 2 VecPoints **/
    VecPoint crossProduct(VecPoint);

    /** Magnitude **/
    double magnitude();

};

#endif