#include "Texture.h"
#include <iostream>
#include <string>

using namespace std;

/*******************/
/* Texture Methods */
/*******************/

// There's nothing here

/*****************/
/* Synth Methods */
/*****************/

Synth::Synth(Image i) :
	sample(i), result(sideLength, sideLength, 1, 3) {}

/***********************/
/* Texture Methods */
/***********************/

Pixel Texture::getPixel(unsigned int x, unsigned int y)
{
	if(x >= image.width() || y >= image.height()) {
		printf("Invalid coordinates: %d, %d\n", x, y);
		return Pixel(0, 0, 0);
	}
	Pixel p;
	p.r = image.data(x, y, 1, R);
	p.g = image.data(x, y, 1, G);
	p.b = image.data(x, y, 1, B);
	return p;
}

Patch Texture::getPatch(int x, int y, int size)
{
	return Patch {this, x, y, size};
}

/*****************/
/* Patch Methods */
/*****************/

Pixel* Patch::getPixel(unsigned int x, unsigned int y)
{
	if(x >= width || y >= width) {
		printf("Invalid coordinates: %d, %d\n", x, y);
		return Pixel(0, 0, 0);
	}
	return sourceImage->getPixel(x + offsetX, y + offsetY);
}

float Patch::difference(Patch& other)
{
	if (other.width != width) {
		cout << "Comparing patches of different sizes!\n";
		return -1;
	}

	float diff = 0;
	Pixel pixelA;
	Pixel pixelB;
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < width; y++) {
			pixelA = getPixel(x, y);
			pixelB = other.getPixel(x, y);
			if(pixelA != nullptr && pixelB != nullptr) {
				// TODO: DO THE THING
			}
		}
	}
}
