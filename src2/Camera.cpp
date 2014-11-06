/* Camera.cpp */

// headers and libraries to use: e.g. #include x
// namespaces to include: e.g. using namespace std

/*
 * The Camera class will be used to create an eye ray for raytracer computation.
 */

class Camera {

  void generateRay(Sample sample, Ray ray);
  /*
   * Creates a ray starting from camera that passes through corresponding pixel
   * (sample.x, sample.y) on the image plane.
   *
   * NOTE: Guide uses Sample& sample and Ray* ray. Does this matter?
   */

};