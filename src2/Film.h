/** Film Class **/
#ifndef FILM_H
#define FILM_H

#include <math.h>
#include <vector>
#include "utility/VecPoint.h"
#include "lodepng.h"
using namespace std;

class Film {
	private:
		/** width and height of file to output **/
		int x, y; 

		/** vector of png **/
		vector<unsigned char> image;

	public:
		/** constructor **/
		Film(){};

		/** getters **/
		int getX() {return this->x;}
		int getY() {return this->y;}
		vector<unsigned char> getImage() {return this->image;}

		/** setters **/
		void setX(int x_val) {this->x = x_val;}
		void setY(int y_val) {this->y = y_val;}
		void setImage(vector<unsigned char> v) {this->image = v;}

		/** set dimensions based on image plane **/
		void setDimensions(VecPoint, VecPoint, VecPoint, VecPoint);

		/** write to PNG **/
    	void encodeOneStep(const char*, std::vector<unsigned char>&, unsigned, unsigned);

    	/** add pixel color **/
    	void pixelate(double, double, double);

    	/** write to image **/
    	void write();
};

#endif