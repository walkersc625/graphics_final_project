#include "Texture.h"
#include <iostream>
#include <string>
#include <jpegio.h>

using namespace std;

/*******************/
/* Texture Methods */
/*******************/

Texture::Texture(const string filepath)
{
	if (!LoadJPEG(filepath, &image)) {
		cout << "load image failed\n";
	} else {
		cout << "image loaded successfully\n";
		printf("\timage width: %d\n", image.width);
		printf("\timage height: %d\n", image.height);
	}
}

/*****************/
/* Synth Methods */
/*****************/

Synth::Synth(Texture t)
{
	sample.data = (Pixel*) t.image.bytes.data();
	sample.width = sampleSideLength;

	pixels.data = new Pixel[size];
	pixels.width = sideLength;
}

Synth::~Synth()
{
	delete[] pixels.data;
}

/***********************/
/* PixelBuffer Methods */
/***********************/

Pixel* PixelBuffer::getPixel(unsigned int x, unsigned int y)
{
	if(x >= width || y >= width) {
		return nullptr;
	}
	unsigned int index = (y * width * sizeof(Pixel)) + (x  * sizeof(Pixel));
	return &data[index];
}

Patch PixelBuffer::getPatchAround(unsigned int x, unsigned int y, unsigned int patchWidth)
{
	return Patch {
		this,
		x - patchWidth/2,
		y - patchWidth/2,
		patchWidth
	};
}

/*****************/
/* Patch Methods */
/*****************/

Pixel* Patch::getPixel(unsigned int x, unsigned int y)
{
	if(x >= width || y >= width || sourceImage == nullptr) {
		return nullptr;
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
	Pixel* pixelA;
	Pixel* pixelB;
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
