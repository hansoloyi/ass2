/* Raytracer.cpp */

#include "Raytracer.h"

Color Raytracer::trace_triangle(Triangle tri, int min_index, VecPoint closest_intersection, Ray ray, int depth, Color color_total) {
  Color ka = this->getScene().getKa().at(min_index);
  Color kd = this->getScene().getKd().at(min_index);
  Color ks = this->getScene().getKs().at(min_index);
  Color kr = this->getScene().getKr().at(min_index);
  double sp = this->getScene().getSp().at(min_index);

  Color lta_term = Color(ka.getR(), ka.getG(), ka.getB());
  lta_term.colorMul(this->getScene().getKaLight());
  color_total.colorAdd(lta_term);

  for (int j = 0; j < this->getScene().getLights().size(); j++) {
    Light light = this->getScene().getLights().at(j);
    Color col_ka = Color(light.getR(),light.getG(),light.getB());
    col_ka.colorMul(ka);

    color_total.colorAdd(col_ka);

    /** create a light ray from intersection to light source **/
    VecPoint light_xyz, lighter, light_vector;
    if (light.isPointLight()) {
      light_xyz = VecPoint(light.getX(), light.getY(), light.getZ(), 1);
      lighter = light_xyz.subtract(closest_intersection);
      light_vector = lighter.normalize();
    } else {
      light_xyz = VecPoint(-light.getX(), -light.getY(), -light.getZ(), 0);
      light_vector = light_xyz.normalize();
    }
    // VecPoint lighter = light_xyz.subtract(closest_intersection);
    // VecPoint light_vector = lighter.normalize();
    VecPoint sha = light_vector.scale(.01);
    VecPoint shadow_origin = closest_intersection.add(sha);
    Ray shadow_ray = Ray(shadow_origin, light_vector); // ray from intersection to light

    VecPoint shadow = VecPoint(0,0,0,0); // checks if object blocking light
    map<int, Sphere> spheres = this->getScene().getSpheres();
    map<int, Triangle> triangles = this->getScene().getTriangles();
    /** checks if there is an object blocking a light ray **/
    for (auto iter=spheres.begin(); iter!=spheres.end(); ++iter) {
      Sphere next_sphere = iter->second;
      if (iter->first != min_index) {
        VecPoint shadow_intersect = shadow_ray.intersectSphere(next_sphere);
        if (!shadow_intersect.isEmpty()) {
          shadow.setX(shadow_intersect.getX());
          shadow.setY(shadow_intersect.getY());
          shadow.setZ(shadow_intersect.getZ());
          shadow.setI(shadow_intersect.getI());
          break;
        }
      }
    }
    for (auto iter=triangles.begin(); iter!=triangles.end(); ++iter) {
      Triangle next_triangle = iter->second;
      if (iter->first != min_index) {
        VecPoint shadow_intersect = shadow_ray.intersectTriangle(next_triangle);
        if (!shadow_intersect.isEmpty()) {
          shadow.setX(shadow_intersect.getX());
          shadow.setY(shadow_intersect.getY());
          shadow.setZ(shadow_intersect.getZ());
          shadow.setI(shadow_intersect.getI());
          break;
        }
      }
    }

    /** if no objects blocking light, calculate phong **/
    if (shadow.isEmpty()) {
      Color adder = tri.shade_tri(ray.getOrigin(), closest_intersection, kd, ks, sp, light);
      color_total.colorAdd(adder);
    }
  }
  VecPoint edge1 = tri.getV2().subtract(tri.getV1());
  VecPoint edge2 = tri.getV3().subtract(tri.getV1());

  VecPoint surface = edge1.crossProduct(edge2);
  VecPoint surface_normal = surface.normalize();

  VecPoint view_ray = ray.getOrigin().subtract(closest_intersection);
  VecPoint view_normal = view_ray.normalize();
  double refl_scale = view_normal.dotProduct(surface_normal) * 2;

  VecPoint component = surface_normal.scale(refl_scale);
  VecPoint r = component.subtract(view_normal);
  VecPoint reflect = r.normalize();

  VecPoint offset = reflect.scale(.01);
  VecPoint offset_position = closest_intersection.add(offset);
  Ray next_ray = Ray(offset_position, reflect);

  Color col =  this->trace(next_ray, depth+1, color_total);
  col.colorMul(kr);
  color_total.colorAdd(col);
  return color_total;
}

Color Raytracer::trace_sphere(Sphere sph, int min_index, VecPoint closest_intersection, Ray ray, int depth, Color color_total) {
  Color ka = this->getScene().getKa().at(min_index);
  Color kd = this->getScene().getKd().at(min_index);
  Color ks = this->getScene().getKs().at(min_index);
  Color kr = this->getScene().getKr().at(min_index);
  double sp = this->getScene().getSp().at(min_index);

  Color lta_term = Color(ka.getR(), ka.getG(), ka.getB());
  lta_term.colorMul(this->getScene().getKaLight());
  color_total.colorAdd(lta_term);

  for (int j = 0; j < this->getScene().getLights().size(); j++) {
    Light light = this->getScene().getLights().at(j);
    Color light_rgb = Color(light.getR(), light.getG(), light.getB());

    Color col_ka = Color(light.getR(),light.getG(),light.getB());
    col_ka.colorMul(ka);

    color_total.colorAdd(col_ka);

    /** create a light ray from intersection to light source **/
    VecPoint light_xyz, lighter, light_vector;
    if (light.isPointLight()) {
      light_xyz = VecPoint(light.getX(), light.getY(), light.getZ(), 1);
      lighter = light_xyz.subtract(closest_intersection);
      light_vector = lighter.normalize();
    } else {
      light_xyz = VecPoint(-light.getX(), -light.getY(), -light.getZ(), 0);
      light_vector = light_xyz.normalize();
    }
    // VecPoint lighter = light_xyz.subtract(closest_intersection);
    // VecPoint light_vector = lighter.normalize();
    VecPoint sha = light_vector.scale(.01);
    VecPoint shadow_origin = closest_intersection.add(sha);
    Ray shadow_ray = Ray(shadow_origin, light_vector); // ray from intersection to light

    VecPoint shadow = VecPoint(0,0,0,0); // checks if object blocking light
    map<int, Sphere> spheres = this->getScene().getSpheres();
    map<int, Triangle> triangles = this->getScene().getTriangles();
    /** checks if there is an object blocking a light ray **/
    for (auto iter=spheres.begin(); iter!=spheres.end(); ++iter) {
      Sphere next_sphere = iter->second;
      if (iter->first != min_index) {
        VecPoint shadow_intersect = shadow_ray.intersectSphere(next_sphere);
        if (!shadow_intersect.isEmpty()) {
          shadow.setX(shadow_intersect.getX());
          shadow.setY(shadow_intersect.getY());
          shadow.setZ(shadow_intersect.getZ());
          shadow.setI(shadow_intersect.getI());
          break;
        }
      }
    }
    for (auto iter=triangles.begin(); iter!=triangles.end(); ++iter) {
      Triangle next_triangle = iter->second;
      if (iter->first != min_index) {
        VecPoint shadow_intersect = shadow_ray.intersectTriangle(next_triangle);
        if (!shadow_intersect.isEmpty()) {
          shadow.setX(shadow_intersect.getX());
          shadow.setY(shadow_intersect.getY());
          shadow.setZ(shadow_intersect.getZ());
          shadow.setI(shadow_intersect.getI());
          break;
        }
      }
    }

    /** if no objects blocking light, calculate phong **/
    if (shadow.isEmpty()) {
      Color adder = sph.shade_point(ray.getOrigin(), closest_intersection, kd, ks, sp, light);
      color_total.colorAdd(adder);
    }
  }
  /** calculate reflectance ray for next recursion **/
  VecPoint center = VecPoint(sph.getX(), sph.getY(), sph.getZ(), 1);
  VecPoint norm = closest_intersection.subtract(center);
  VecPoint surface_normal = norm.normalize();

  VecPoint view_ray = ray.getOrigin().subtract(closest_intersection);
  VecPoint view_normal = view_ray.normalize();
  double refl_scale = view_normal.dotProduct(surface_normal) * 2;

  VecPoint component = surface_normal.scale(refl_scale);
  VecPoint r = component.subtract(view_normal);
  VecPoint reflect = r.normalize();

  VecPoint offset = reflect.scale(.01);
  VecPoint offset_position = closest_intersection.add(offset);
  Ray next_ray = Ray(offset_position, reflect);

  Color col =  this->trace(next_ray, depth+1, color_total);
  col.colorMul(kr);
  color_total.colorAdd(col);
  return color_total;
}
/*
 * Computes the color of a ray.
 */
Color Raytracer::trace(Ray ray, int depth, Color color_total)
{
  if (depth > 1) {
    return color_total;
  }
  else {
    double min_distance = 1000000.0;
    int min_index; //index of sphere we hit
    VecPoint closest_intersection = VecPoint(0,0,0,0);
    map<int, Sphere> spheres = this->getScene().getSpheres();
    map<int, Triangle> triangles = this->getScene().getTriangles();

    //check if closest intersection is sphere
    for (auto iter=spheres.begin(); iter!=spheres.end(); ++iter) {
      Sphere curr_sphere = iter->second;
      VecPoint inter = ray.intersectSphere(curr_sphere);
      if (!inter.isEmpty()) {
        VecPoint distance_vector = inter.subtract(ray.getOrigin());
        double distance = distance_vector.magnitude();
        if (distance < min_distance) {
          min_distance = distance;
          min_index = iter->first;
          closest_intersection.setX(inter.getX());
          closest_intersection.setY(inter.getY());
          closest_intersection.setZ(inter.getZ());
          closest_intersection.setI(inter.getI());
        }
      }
    }
    //check if closest intersection is triangle
    for (auto iter=triangles.begin(); iter!=triangles.end(); ++iter) {
      Triangle curr_triangle = iter->second;
      VecPoint inter = ray.intersectTriangle(curr_triangle);
      if (!inter.isEmpty()) {
        VecPoint distance_vector = inter.subtract(ray.getOrigin());
        double distance = distance_vector.magnitude();
        if (distance < min_distance) {
          min_distance = distance;
          min_index = iter->first;
          closest_intersection.setX(inter.getX());
          closest_intersection.setY(inter.getY());
          closest_intersection.setZ(inter.getZ());
          closest_intersection.setI(inter.getI());
        }
      }
    }
    if (closest_intersection.isEmpty()) {
      return color_total;
    }  else {
      /** if the nearest intersect point is not (0,0,0,0) 
       ** then check for light ray intersections and add 
       ** to color accordingly
       **/

      /* sphere that is intersected and coefficients associated with it **/
      map<int, Sphere>::iterator it;
      map<int, Triangle>::iterator it2;
      it=spheres.find(min_index);
      if (it != spheres.end()) {
        Sphere sph = it->second;
        return this->trace_sphere(sph, min_index, closest_intersection, ray, depth, color_total);
      } else {
        it2=triangles.find(min_index);
        Triangle tri = it2->second;
        return this->trace_triangle(tri, min_index, closest_intersection, ray, depth, color_total);
      }
    } 
  } 
}



