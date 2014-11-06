/* Color.cpp */

#include "Color.h"

Color::Color(double red, double green, double blue)
{
  if (red < 0 || green < 0 || blue < 0 || red > 1 || green > 1 || blue > 1)
  {
    cout << "Color must be between 0.0 and 1.0!\n";
    exit(EXIT_FAILURE);
  } else {
    this->r = red;
    this->g = green;
    this->b = blue;
  }
}

void Color::display()
{
  printf("(%f, %f, %f)", \
  this->getR(), this->getG(), this->getB());
}

void Color::colorAdd(Color a)
{
  double r = a.getR() + this->getR();
  double g = a.getG() + this->getG();
  double b = a.getB() + this->getB();
  this->setR(r);
  this->setG(g);
  this->setB(b);
}

void Color::colorSub(Color a)
{
  double r = this->getR() - a.getR();
  double g = this->getG() - a.getG();
  double b = this->getB() - a.getB();
  this->setR(r);
  this->setG(g);
  this->setB(b);
}

void Color::colorMul(Color a)
{
  double r = this->getR() * a.getR();
  double g = this->getG() * a.getG();
  double b = this->getB() * a.getB();
  this->setR(r);
  this->setG(g);
  this->setB(b);
}

void Color::colorScale(double factor)
{
  double r = this->getR() * factor;
  double g = this->getG() * factor;
  double b = this->getB() * factor;
  this->setR(r);
  this->setG(g);
  this->setB(b);
}


