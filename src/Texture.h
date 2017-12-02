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
	Texture(Image i): image(i), pixelsFilled(i.width(),
		vector<bool>(i.height(), false)) {}
	Pixel getPixel(uint x, uint y) const;
	void setPixel(uint x, uint y, Pixel p);
	Patch getPatch(int offsetX, int offsetY, uint size);
};

//Small sampling window for algorithm
struct Patch {
	Texture* sourceImage;
	int offsetX;
	int offsetY;
	uint width;
	Pixel getPixel(uint x, uint y) const;
	Pixel getCenterPixel() const;
	void setPixel(uint x, uint y, Pixel p);
	void copyPatch(Patch& src);
	float difference(const Patch& other) const;
};

//Full texture being generated
class Synth {
private:
	void placeSeed();
public:
	Texture sample;
	Texture result;

	uint patchSize; // size n means an n^2 pxel patch

	static constexpr int sideLength = 250;
	static constexpr int sampleSideLength = 250;

	Synth(Image i, uint patchSize);
	void synthesize();
	void assignColor(uint a, uint b);
};

#endif
