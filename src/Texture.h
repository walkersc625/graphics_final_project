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

static const Pixel error_pixel = Pixel(-1, -1, -1);

struct Patch;

struct Texture {
	Image image;
	vector<vector<bool>> pixelsFilled;
	Texture(Image i): image(i), pixelsFilled(i.width(), vector<bool>(i.height(), false)) {}
	Pixel getPixel(unsigned int x, unsigned int y) const;
	void setPixel(unsigned int x, unsigned int y, Pixel p);
	Patch getPatch(unsigned int offsetX, unsigned int offsetY, unsigned int size);
};

//Small sampling window for algorithm
struct Patch {
	Texture* sourceImage;
	unsigned int offsetX;
	unsigned int offsetY;
	unsigned int width;
	Pixel getPixel(unsigned int x, unsigned int y) const;
	void setPixel(unsigned int x, unsigned int y, Pixel p);
	float difference(const Patch& other) const;
};

//Full texture being generated
class Synth {
private:
	void placeSeed();
public:
	Texture sample;
	Texture result;

	unsigned int patchSize;

	static constexpr int sideLength = 750;
	static constexpr int sampleSideLength = 250;

	Synth(Image i, unsigned int patchSize);
	void synthesize();
};

#endif