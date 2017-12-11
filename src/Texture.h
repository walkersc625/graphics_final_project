#ifndef TEXTURE_H
#define TEXTURE_H

#include <vector>
#include <string>
#include <tuple>

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
typedef tuple<int, int, int> (*ParamUpdateFunc)(int, int, int);

enum Colors {
	R,
	G,
	B
};

enum SeedType {
	WHOLE_IMAGE,
	RAND_PATCH
};

enum SeedPlacement {
	CENTER,
	CORNER
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
	void clear();
};

//Small sampling window for algorithm
struct Patch {
	Texture* sourceImage;
	int offsetX;
	int offsetY;
	int width;
	vector<pair<int, int>> validPixels;
	Pixel getPixel(int x, int y) const;
	Pixel getCenterPixel() const;
	void setPixel(int x, int y, Pixel p);
	void copyPatch(Patch& src);
	float difference(const Patch& other, float** gaussian) const;
	void fillValidPixels();
};

//Full texture being generated
class Synth {
private:
	bool sanityChecks();
	Patch getSeed();
	void synthesize_from_top_left(Patch seed);
	void synthesize_from_center(Patch seed);
	void assignColor(uint a, uint b);
	void assignColor(pair<int, int> p);
	float** generateGaussian(int size);
public:
	int patchSize; // size n means an n^2 pxel patch

	bool useGaussian;
	float** gaussian;

	int sideLength = 512;
	int sampleSideLength;

	SeedPlacement seedPlacement = CENTER;
	SeedType seedType = RAND_PATCH;

	Texture sample;
	Texture result;

	Synth() = default;
	//Synth(const Synth& rhs) = default;
	Synth(Image i, int patchSize, bool small, int resultSideLength);
	void synthesize();
    void thread_synthesize(bool vert, int start, int min, int max, ParamUpdateFunc paramUpdate);
};

#endif
