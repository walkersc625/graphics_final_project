#ifndef TEXTURE_H
#define TEXTURE_H

#include <vector>
#include <string>

#include <image.h>
#include <GL/glew.h>

using namespace std;

struct PixelBuffer;
struct Patch;

//For loading sample textures
struct Texture {
	Image image;
	GLuint id;

	Texture(const string filepath);
};

//Color information only
struct Pixel {
	unsigned char r;
	unsigned char g;
	unsigned char b;
};

//Small sampling window for algorithm
struct Patch {
	PixelBuffer* sourceImage;
	unsigned int offsetX;
	unsigned int offsetY;
	unsigned int width;
	Pixel* getPixel(unsigned int x, unsigned int y);
	float difference(Patch& other);
};

//Self-explanatory
struct PixelBuffer {
	Pixel* data;
	unsigned int width;

	Pixel* getPixel(unsigned int x, unsigned int y);
	Patch getPatchAround(unsigned int x, unsigned int y, unsigned int patchWidth);
};

//Full texture being generated
class Synth {

	Synth(Texture t);
	~Synth();

	PixelBuffer sample;
	PixelBuffer pixels;

	static constexpr int size = 750 * 750;
	static constexpr int sideLength = 750;
	static constexpr int sampleSize = 250 * 250;
	static constexpr int sampleSideLength = 250;

};

#endif