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
	Pixel getPixel(int x, int y) const;
	void setPixel(int x, int y, Pixel p);
	Patch getPatch(int offsetX, int offsetY, int size);
};

//Small sampling window for algorithm
struct Patch {
	Texture* sourceImage;
	int offsetX;
	int offsetY;
	int width;
	bool checkPixels = false;
	vector<pair<int, int>> validPixels;
	Pixel getPixel(int x, int y) const;
	Pixel getCenterPixel() const;
	void setPixel(int x, int y, Pixel p);
	void copyPatch(Patch& src);
	float difference(const Patch& other) const;
};

//Full texture being generated
class Synth {
private:
	bool sanityChecks();
	void placeSeed();
public:
	Texture sample;
	Texture result;

	int patchSize; // size n means an n^2 pxel patch

	static constexpr int sideLength = 250;
	static constexpr int sampleSideLength = 250;

	Synth(Image i, int patchSize);
	void synthesize();
	void assignColor(uint a, uint b);
};

#endif