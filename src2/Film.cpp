/* Film.cpp */
#include "Film.h"


/** sets dimension of output file **/
void Film::setDimensions(VecPoint ll, VecPoint lr, VecPoint ul, VecPoint ur) {
  VecPoint width = lr.subtract(ll); // width vector image plane
  VecPoint height = ul.subtract(ll); // height vector of image plane
  int x_mag = (int)(ceil(sqrt(pow(width.getX(), 2) + pow(width.getY(), 2) + pow(width.getZ(), 2))));
  int y_mag = (int)(ceil(sqrt(pow(height.getX(), 2) + pow(height.getY(), 2) + pow(height.getZ(), 2))));
  int minimum = min(x_mag, y_mag);
  int scale = (int)(ceil(1000/minimum));
  x_mag = x_mag * scale;
  y_mag = y_mag * scale;
  if (x_mag > 3000) {
    this->setX(3000);
  }
  else {
    this->setX(x_mag);
  }
  if (y_mag > 3000) {
    this->setY(3000);
  } else {
    this->setY(y_mag);
  }
}

/** for writing **/
void Film::encodeOneStep(const char* filename, std::vector<unsigned char>& image, unsigned width, unsigned height)
{
  //Encode the image
  unsigned error = lodepng::encode(filename, image, width, height);

  //if there's an error, display it
  if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}

void Film::pixelate(double r, double g, double b) {
  this->image.push_back(r * 255);
  this->image.push_back(g * 255);
  this->image.push_back(b * 255);
  this->image.push_back(255);
}

void Film::write() {
  const char* file_name = "test";
  this->encodeOneStep(file_name, image, this->getX(), this->getY());
}


