#ifndef TEXTURE_H
#define TEXTURE_H

#include <vector>
#include <string>

#include <GL/glew.h>
#include <CImg/CImg.h>
#include <glm/glm.hpp>

using namespace std;
using namespace cimg_library;
using namespace glm;

struct PixelBuffer;
struct Patch;

typedef CImg<unsigned char> Image;
typedef uvec3 Pixel;

enum Colors {
	R,
	G,
	B
};

struct Patch;

struct Texture {
	Image image;
	Texture(Image i): image(i) {}
	Pixel getPixel(unsigned int x, unsigned int y);
	Patch getPatch(int offsetX, int offsetY, int size);
};

//Small sampling window for algorithm
struct Patch {
	Texture* sourceImage;
	unsigned int offsetX;
	unsigned int offsetY;
	unsigned int width;
	Pixel getPixel(unsigned int x, unsigned int y);
	float difference(Patch& other);
};

//Full texture being generated
class Synth {

	Synth(Image t);

	Texture sample;
	Texture result;

	static constexpr int sideLength = 750;
	static constexpr int sampleSideLength = 250;

};

#endif