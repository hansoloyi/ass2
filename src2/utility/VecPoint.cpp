/* VecPoint.cpp */

#include "VecPoint.h"

VecPoint::VecPoint(double xpos, double ypos, double zpos, double choose)
{
  if (choose != 1 && choose != 0) {
    cout << "4th element of vector must be 0 or 1\n";
    exit(EXIT_FAILURE);
  }
  x = xpos;
  y = ypos;
  z = zpos;
  i = choose;
}

void VecPoint::display()
{
  printf("(%f, %f, %f, %f)", \
    this->getX(), this->getY(), this->getZ(), this->getI());
}

bool VecPoint::isEmpty()
{
  return this->getX() == 0 and this->getY() == 0 and \
         this->getZ() == 0 and this->getI() == 0;
}

VecPoint VecPoint::add(VecPoint a)
{
  double x = a.getX() + this->getX();
  double y = a.getY() + this->getY();
  double z = a.getZ() + this->getZ();
  double i = a.getI() + this->getI();
  VecPoint result = VecPoint(x, y, z, i);
  if (i > 1) {
    cout << "Cannot add 2 points\n";
    exit(EXIT_FAILURE);
  } else {
    return result;
  }
}

VecPoint VecPoint::addForP(VecPoint a) {
  double x = a.getX() + this->getX();
  double y = a.getY() + this->getY();
  double z = a.getZ() + this->getZ();
  VecPoint result = VecPoint(x, y, z, 1);
  return result;
}

VecPoint VecPoint::subtract(VecPoint a)
{
  double x = this->getX() - a.getX() ;
  double y = this->getY() - a.getY() ;
  double z = this->getZ() - a.getZ() ;
  double i = this->getI() - a.getI() ;
  VecPoint result = VecPoint(x, y, z, i);
  if (i < 0) {
    cout << "Malformed input vector: 4th element negative\n";
    exit(EXIT_FAILURE);
  } else {
    return result;
  }
}

VecPoint VecPoint::scale(double factor)
{
  double i = this->getI();
  if (i != 0) {
    cout << "Cannot scale non-vector objects\n";
    exit(EXIT_FAILURE);
  } else {
    double x = this->getX() * factor;
    double y = this->getY() * factor;
    double z = this->getZ() * factor;
    VecPoint result = VecPoint(x, y, z, i);
    return result;
  }
}

VecPoint VecPoint::scaleForP(double factor) {
  double x = this->getX() * factor;
  double y = this->getY() * factor;
  double z = this->getZ() * factor;
  VecPoint result = VecPoint(x,y,z,1);
  return result;
}

VecPoint VecPoint::normalize()
{
  if (this->getI() != 0)
  {
    cout << "Cannot normalize non-vector object\n";
    exit(EXIT_FAILURE);
  } else {
    double normalizer = sqrt(pow(this->getX(), 2) + pow(this->getY(), 2) + pow(this->getZ(), 2));
    double newX = this->getX()/normalizer;
    double newY = this->getY()/normalizer;
    double newZ = this->getZ()/normalizer;
    VecPoint result = VecPoint(newX, newY, newZ, 0);
    return result;
  }
}

double VecPoint::dotProduct(VecPoint v) {
  return this->getX()*v.getX() + this->getY()*v.getY() + this->getZ()*v.getZ();
}

VecPoint VecPoint::crossProduct(VecPoint v) {
  double x, y, z;
  x = this->getY() * v.getZ() - this->getZ() * v.getY();
  y = this->getZ() * v.getX() - this->getX() * v.getZ();
  z = this->getX() * v.getY() - this->getY() * v.getX();
  VecPoint result = VecPoint(x, y, z, 0);
  return result;
}

double VecPoint::magnitude() {
  return sqrt(pow(this->getX(), 2) + pow(this->getZ(), 2) + pow(this->getY(), 2));
}


