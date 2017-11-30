#include "Texture.h"
#include <iostream>
#include <string>
#include <glm/gtx/norm.hpp>
#include <cstdlib>

using namespace std;

/*******************/
/* Texture Methods */
/*******************/

Pixel Texture::getPixel(unsigned int x, unsigned int y) const
{
	if(x >= (unsigned int)image.width() || y >= (unsigned int)image.height() || !pixelsFilled[x][y]) {
		printf("Invalid coordinates: %d, %d\n", x, y);
		return error_pixel;
	}
	Pixel p;
	p.r = (unsigned int)(*image.data(x, y, 0, R));
	p.g = (unsigned int)(*image.data(x, y, 0, G));
	p.b = (unsigned int)(*image.data(x, y, 0, B));
	return p;
}

void Texture::setPixel(unsigned int x, unsigned int y, Pixel p) {
	if(x >= (unsigned int)image.width() || y >= (unsigned int)image.height()) {
		printf("Invalid coordinates: %d, %d\n", x, y);
	}
	pixelsFilled[x][y] = true;
	image(x, y, 0, R) = (unsigned char)p.r;
	image(x, y, 0, G) = (unsigned char)p.g;
	image(x, y, 0, B) = (unsigned char)p.b;
}

Patch Texture::getPatch(unsigned int x, unsigned int y, unsigned int size)
{
	return Patch {this, x, y, size};
}

/*****************/
/* Patch Methods */
/*****************/

Pixel Patch::getPixel(unsigned int x, unsigned int y) const
{
	if(x >= width || y >= width) {
		printf("Invalid coordinates: %d, %d\n", x, y);
		return error_pixel;
	}
	return sourceImage->getPixel(x + offsetX, y + offsetY);
}

void Patch::setPixel(unsigned int x, unsigned int y, Pixel p) {
	if(x >= width || y >= width) {
		printf("Invalid coordinates: %d, %d\n", x, y);
	}
	sourceImage->setPixel(x + offsetX, y + offsetY, p);
}

float Patch::difference(const Patch& other) const
{
	if (other.width != width) {
		cout << "Comparing patches of different sizes!\n";
		return -1;
	}

	float diff = 0;
	int pixelCount = 0;
	Pixel pixelA;
	Pixel pixelB;
	for (unsigned int x = 0; x < width; x++) {
		for (unsigned int y = 0; y < width; y++) {
			pixelA = getPixel(x, y);
			pixelB = other.getPixel(x, y);
			if(pixelA != error_pixel && pixelB == error_pixel) {
				diff += l1Norm(pixelA, pixelB);
				pixelCount++;
			}
		}
	}
	return diff / pixelCount;
}

/*****************/
/* Synth Methods */
/*****************/

Synth::Synth(Image i, unsigned int patchSize) :
		sample(i), result(Image(sideLength, sideLength, 1, 3)), patchSize{patchSize}
{
	sample.pixelsFilled = vector<vector<bool>>(sideLength, vector<bool>(sideLength, true));
}

void Synth::synthesize() {
	placeSeed();
}

void Synth::placeSeed() {
	unsigned int randX = rand() % (sampleSideLength - patchSize);
	unsigned int randY = rand() % (sampleSideLength - patchSize);
	Patch samplePatch = sample.getPatch(randX, randY, patchSize);
	Patch centerPatch = result.getPatch(sideLength/2 - patchSize/2, sideLength/2 - patchSize/2, patchSize);
	for(unsigned int x = 0; x < patchSize; x++) {
		for(unsigned int y = 0; y < patchSize; y++) {
			centerPatch.setPixel(x, y, samplePatch.getPixel(x, y));
		}
	}
}