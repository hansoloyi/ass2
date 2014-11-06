/* Light.cpp */

#include "Light.h"

Light::Light(double x, double y, double z, double r, double g, double b, double fo, 
  bool isPoint)
{
  this->x = x;
  this->y = y;
  this->z = z;
  this->r = r;
  this->g = g;
  this->b = b;
  this->fallOff = fo;
  this->point = isPoint;
}

void Light::display()
{
  printf("position: (%f, %f, %f)\nrgb: (%f, %f, %f)\nfalloff: %f\n",
  this->getX(), this->getY(), this->getZ(), this->getR(), this->getG(),
  this->getB(), this->fallOff);
  if (this->isPointLight())
  {
    cout << "type: Point";
  } else 
  {
    cout << "type: Directional\n";
  }

}