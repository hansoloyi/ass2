/* Sphere.cpp */

#include "Sphere.h"

Sphere::Sphere(double x, double y, double z, double radius)
{
  this->x = x;
  this->y = y;
  this->z = z;
  this->r = radius;
}

Color Sphere::shade_point(VecPoint cam, VecPoint pos, Color kd, Color ks, \
  double power, Light light)
{
  Color result = Color(0,0,0);
  VecPoint light_xyz = VecPoint(light.getX(), light.getY(), light.getZ(), 1.0);
  Color light_rgb = Color(light.getR(), light.getG(), light.getB());
  VecPoint center = VecPoint(this->getX(), this->getY(), this->getZ(), 1);
  VecPoint surface = pos.subtract(center);
  VecPoint surface_normal = surface.normalize();

  VecPoint light_vec;

  if (light.isPointLight())
  {
    light_vec = light_xyz.subtract(pos);
  }
  else
  {
    light_vec = VecPoint(-light_xyz.getX(), -light_xyz.getY(), -light_xyz.getZ(), 0);
  }
  VecPoint light_normal = light_vec.normalize();

  double refl = light_normal.dotProduct(surface_normal) * 2;
  VecPoint comp1 = surface_normal.scale(refl);
  VecPoint r = comp1.subtract(light_normal);
  VecPoint reflectance = r.normalize();

  VecPoint view = cam.subtract(pos);
  VecPoint view_normal = view.normalize();

  double zero = 0;
  Color diff_color = Color(light.getR(), light.getG(), light.getB());
  Color spec_color = Color(light.getR(), light.getG(), light.getB());

  //diffuse term  
  double diff_scale = max(light_normal.dotProduct(surface_normal), zero);
  diff_color.colorScale(diff_scale);
  diff_color.colorMul(kd);
  
  //specular term
  double spec_scale = pow(max(view_normal.dotProduct(reflectance), zero), power);
  spec_color.colorScale(spec_scale);
  spec_color.colorMul(ks);

  result.colorAdd(diff_color);
  result.colorAdd(spec_color);
  return result;
}

void Sphere::display()
{
  printf("(%f, %f, %f, radius: %f)", \
    this->getX(), this->getY(), this->getZ(), this->getRadius());
}