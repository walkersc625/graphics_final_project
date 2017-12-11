#include "Texture.h"
#include <iostream>
#include <string>
#include <glm/gtx/norm.hpp>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include <thread>

#define GRAY (unsigned char) 100

using namespace std;

/*******************/
/* Texture Methods */
/*******************/ 

Pixel Texture::getPixel(int x, int y) const
{
	if (x >= image.width() || y >= image.height() || 
		x < 0 || y < 0 || !pixelsFilled[x][y]) {
		return error_pixel;
	}

	Pixel p;
	p.r = (uint)(*image.data(x, y, 0, R));
	p.g = (uint)(*image.data(x, y, 0, G));
	p.b = (uint)(*image.data(x, y, 0, B));
	return p;
}

void Texture::setPixel(int x, int y, Pixel p)
{
	if (x >= image.width() || y >= image.height()) {
		printf("setPixel in texture\n");
		printf("Invalid coordinates: %d, %d\n", x, y);
		printf("image width: %d, height: %d\n", image.width(), image.height());
	}
	pixelsFilled[x][y] = true;
	image(x, y, 0, R) = (unsigned char)p.r;
	image(x, y, 0, G) = (unsigned char)p.g;
	image(x, y, 0, B) = (unsigned char)p.b;
}

Patch Texture::getPatch(int x, int y, int size)
{
	return Patch {this, x, y, size};
}

void Texture::clear()
{
	for (int x = 0; x < image.width(); x++) {
		for (int y = 0; y < image.height(); y++) {
			image(x, y, 0, R) = GRAY;
			image(x, y, 0, G) = GRAY;
			image(x, y, 0, B) = GRAY;
		}
	}
}

/*****************/
/* Patch Methods */
/*****************/

Pixel Patch::getPixel(int x, int y) const
{
	if (x >= width || y >= width) {
		printf("getPixel in patch\n");
		printf("Invalid coordinates: %d, %d\n", x, y);
		return error_pixel;
	}
	return sourceImage->getPixel(x + offsetX, y + offsetY);
}

Pixel Patch::getCenterPixel() const
{
	return getPixel(width/2, width/2);
}

void Patch::setPixel(int x, int y, Pixel p)
{
	if (x >= width || y >= width) {
		printf("setPixel in patch\n");
		printf("Invalid coordinates: %d, %d\n", x, y);
	}
	sourceImage->setPixel(x + offsetX, y + offsetY, p);
}

void Patch::copyPatch(Patch& src)
{
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < width; y++) {
			setPixel(x, y, src.getPixel(x, y));
		}
	}
}

// l1_Norm wasn't working because of unsigned issues
inline float pixel_L1Norm(Pixel pixelA, Pixel pixelB) {
	float d = 0;
	d += pixelA.x - pixelB.x < 256 ? pixelA.x-pixelB.x : pixelB.x-pixelA.x;
	d += pixelA.y - pixelB.y < 256 ? pixelA.y-pixelB.y : pixelB.y-pixelA.y;
	d += pixelA.z - pixelB.z < 256 ? pixelA.z-pixelB.z : pixelB.z-pixelA.z;
	return d;
}

float Patch::difference(const Patch& other, float** gaussian) const
{
	if (other.width != width) {
		cout << "Comparing patches of different sizes!\n";
		return -1;
	}

	uint diff = 0;
	Pixel pixelA;
	Pixel pixelB;

	// Otherwise go through whole patch and store for later
	
	for (pair<int,int> p : validPixels){
			pixelA = getPixel(p.first, p.second);
			pixelB = other.getPixel(p.first, p.second);
			diff += pixel_L1Norm(pixelA, pixelB) * gaussian[p.first][p.second];
	}
	
	// Dividing by sum again seems to make it worse.
	// Maybe with the gaussian multiplier it's so small that it becomes innacurate?
	// Either way since we're always comparing the same patch we're only comparing
	// this to other things with the same number of pixels, so we shouldn't lose
	// any accuracy by not normalizing.
	return diff;// / validPixels.size();
}

void Patch::fillValidPixels()
{
	for (int i =0; i<width; i++){
		for (int j=0; j<width; j++){
			if (i+offsetX >= 0 && i+offsetX < sourceImage->image.width() &&
				j+offsetY >= 0 && j+offsetY < sourceImage->image.height()) {
				if (sourceImage->pixelsFilled[i+offsetX][j+offsetY]) {
					validPixels.push_back(make_pair(i,j));
				}
			}
		}
	}
}

/*****************/
/* Synth Methods */
/*****************/

Synth::Synth(Image i, int patchSize, bool small, int resultSideLength) :
		sample(i), result(Image()),
		patchSize{patchSize}, sampleSideLength{i.width()}
{
	/* check for size inversion */
	if (small) {
		resultSideLength = 128;
		if (patchSize > 128) {
			patchSize = 127;
		}
	}

	/* save side length for later use */
	sideLength = resultSideLength;

	/* set all pixels in sample to true */
	sample.pixelsFilled =
		vector<vector<bool>>(sampleSideLength,
			vector<bool>(sampleSideLength, true));

	result = Texture(Image(resultSideLength, resultSideLength, 1, 3));
	result.clear();

	gaussian = generateGaussian(patchSize);
}

float** Synth::generateGaussian(int size) {
	float** gaussian = new float*[size];
	for(int i = 0; i < size; i++) {
		gaussian[i] = new float[size];
	}

	double sigma = 1.0;
	double r, s = 2.0 * sigma * sigma;
 
	// sum is for normalization
	double sum = 0.0;

	for (int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++) {
			float x = i - ((size-1)/2.0);
			float y = j - ((size-1)/2.0);
			r = x*x + y*y;
			gaussian[i][j] = exp((-r/s)/(M_PI * s));
			sum += gaussian[i][j];
		}
    }
 
	// normalize
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			gaussian[i][j] /= sum;
		}
	}
	return gaussian;
}

void Synth::synthesize() {
    if (!sanityChecks()) return;

    Patch seed;
    if(seedType == WHOLE_IMAGE) {
        seed = sample.getPatch(0, 0, sampleSideLength);
    } else {
        seed = getSeed();
    }

    if(seedPlacement == CENTER) {
        synthesize_from_center(seed);
    } else {
        synthesize_from_top_left(seed);
    }
}

/* Synthesizes a line (vertical or horizontal), from min - max inclusive.
	 start is the value of the x/y coordinate that doesn't vary
*/
void Synth::thread_synthesize(bool vert, int start, int min, int max, ParamUpdateFunc updateParams)
{
	tuple<int, int, int> params;
	while(min >= 0 && max < sideLength) {
		for(int i=min; i<=max; i++) {
			if(vert) {
				assignColor(start, i);
			}
			else {
				assignColor(i, start);
			}
		}
		params = updateParams(start, min, max);
		start = get<0>(params);
		min = get<1>(params);
		max = get<2>(params);
	}
}

tuple<int, int, int> topLeftParamUpdate(int a, int dummy1, int dummy2) {
	// B and c are dummy variables. Only a changes (and a === c)
	return std::make_tuple(a + 1, 0, a + 1);
}

void Synth::synthesize_from_top_left(Patch seed)
{
	int seedSize = seed.width;
	Patch cornerPatch = result.getPatch(0, 0, seedSize);
	cornerPatch.copyPatch(seed);

	/* Loop around seed, need to synthesize middle pixel in patch */
	int a = seedSize;
	thread t1(&Synth::thread_synthesize, this, true, a, 0, a, topLeftParamUpdate);
	thread t2(&Synth::thread_synthesize, this, false, a, 0, a, topLeftParamUpdate);
	t1.join();
	t2.join();
}

tuple<int, int, int> centerTopAndLeftParamUpdate(int a, int dummy, int b) {
	return std::make_tuple(a - 1, a - 1, b + 1);
}

tuple<int, int, int> centerBotAndRightParamUpdate(int b, int a, int dummy) {
	return std::make_tuple(b + 1, a - 1, b + 1);
}

void Synth::synthesize_from_center(Patch seed)
{
	int seedSize = seed.width;
	Patch centerPatch = result.getPatch((sideLength - seedSize)/2, (sideLength - seedSize)/2, seedSize);
	centerPatch.copyPatch(seed);

	cout << "SideLength=" << sideLength << endl;
	cout << "image width=" << result.image.width() << endl;

	/* Loop around seed, need to synthesize middle pixel in patch */
	int a = (sideLength-seedSize)/2 - 1;
	int b = (sideLength-seedSize)/2 + seedSize;
	thread t1(&Synth::thread_synthesize, this, true, a, a, b, centerTopAndLeftParamUpdate); // Left
	thread t2(&Synth::thread_synthesize, this, false, a, a, b, centerTopAndLeftParamUpdate); // Top
	thread t3(&Synth::thread_synthesize, this, true, b, a, b, centerBotAndRightParamUpdate); // Right
	thread t4(&Synth::thread_synthesize, this, false, b, a, b, centerBotAndRightParamUpdate); // Bottom
	t1.join();
	t2.join();
	t3.join();
	t4.join();

	// Do last row and column if seed was not perfectly centered
	// (not really any need to multithread this)
	if(!result.pixelsFilled[sideLength-1][sideLength-1]) {
		for(int i=0; i < sideLength; i++) {
			assignColor(sideLength-1, i);
			assignColor(i, sideLength-1);
		}
	}	
}

bool Synth::sanityChecks()
{
	if (patchSize > sampleSideLength) {
		printf("Error patchsize %d is greater than sampleSize %d\n", patchSize, sampleSideLength);
		return false;
	}
	if (patchSize > sideLength) {
		printf("Error patchsize %d is greater than result size %d\n", patchSize, sideLength);
		return false;
	}
	if (sideLength < sampleSideLength) {
            if(seedType == RAND_PATCH) {
		printf("Result size %d is smaller than sample size %d (not an error but you're weird)\n", sideLength, sampleSideLength);
            } else {
                printf("Result size %d is smaller than sample size %d (either choose a larger result or use a random patch as a starting seed)\n", sideLength, sampleSideLength);
                return false;
            }
	}
	return true;
}

/*Copies a randomly chosen seed patch from sample to (0,0) of result.*/
Patch Synth::getSeed()
{
	srand(time(NULL));
	uint randX = rand() % (sampleSideLength - patchSize);
	uint randY = rand() % (sampleSideLength - patchSize);

	Patch samplePatch = sample.getPatch(randX, randY, patchSize);
	return samplePatch;
}

// assignColor
// 1. Transform (a,b) into result patch
// 2. Iterate over all sample patches and compute differences
// 3. Pick sample patch based on differences
// 4. Color pixel (a,b) off of center of chosen patch 
void Synth::assignColor(uint a, uint b)
{
	//result patch with (x, y) as center pixel
	Patch res = result.getPatch(a - patchSize/2, b - patchSize / 2, patchSize);
	res.fillValidPixels();

	//vector to store differences
	uint sampleSize = powf(sampleSideLength, 2);
	vector<pair<float, pair<uint, uint>>> diffs;

	//get differences from all sample patches
	Patch sam;
	for (int i = 0; i < sampleSideLength - patchSize; i++) {
		for (int j = 0; j < sampleSideLength - patchSize; j++) {
			sam = sample.getPatch(i, j, patchSize);
			float diff = res.difference(sam, gaussian);
			if (diffs.size() <= 5) {
				diffs.push_back(make_pair(diff, make_pair(i, j)));
			} else {
				diffs[5] = make_pair(diff, make_pair(i, j));
				sort(begin(diffs), end(diffs));
			}
		}
	}

	// "similarity measure" is 100/difference
	// find sum of similarities
	float similaritySum = 0;
	for (int i = 0; i < 5; i++) {
		pair<float, pair<uint, uint>> candidate = diffs[i];
		similaritySum += 100.0 / candidate.first;
	}

	// Select patch with probability proportional to its similarity
	srand(time(NULL));
	float r = (float)rand() * (similaritySum / RAND_MAX);
	pair<float, pair<uint, uint>> chosenDiff;
	float similarity;
	for (int i = 0; i < 5; i++) {
		pair<float, pair<uint, uint>> candidate = diffs[i];
		similarity = 100.0 / candidate.first;
		if (r <= similarity) {
			chosenDiff = candidate;
			break;
		}
		r -= similarity;
	}

	//color pixel (a, b) of result from chosen patch
	uint x = chosenDiff.second.first;
	uint y = chosenDiff.second.second;
	sam = sample.getPatch(x, y, patchSize);
	res.setPixel(patchSize/2, patchSize/2, sam.getCenterPixel());
}

void Synth::assignColor(pair<int, int> p) {
	return assignColor(p.first, p.second);
}
