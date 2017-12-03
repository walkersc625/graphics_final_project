#include "Texture.h"
#include <iostream>
#include <string>
#include <glm/gtx/norm.hpp>
#include <cstdlib>
#include <cmath>

using namespace std;

/*******************/
/* Texture Methods */
/*******************/ 

Pixel Texture::getPixel(int x, int y) const
{
	if(x >= image.width() || y >= image.height() || 
		x < 0 || y < 0 || !pixelsFilled[x][y]) {
		// printf("getPixel in texture\n");
		// printf("Invalid coordinates: %d, %d\n", x, y);
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

float Patch::difference(const Patch& other) const
{
	if (other.width != width) {
		cout << "Comparing patches of different sizes!\n";
		return -1;
	}

	uint diff = 0;
	Pixel pixelA;
	Pixel pixelB;

	// Otherwise go through whole patch and store for later
	
	for(pair<int,int> p : validPixels){
			pixelA = getPixel(p.first, p.second);
			pixelB = other.getPixel(p.first, p.second);
			diff += pixel_L1Norm(pixelA, pixelB);
	}
	
	
	return diff / validPixels.size();
}

void Patch::fillValidPixels()
{
	for(int i =0; i<width; i++){
		for(int j=0; j<width; j++){
			if(i+offsetX >= 0 && i+offsetX < sourceImage->image.width() &&
				j+offsetY >= 0 && j+offsetY < sourceImage->image.height()) {
				if(sourceImage->pixelsFilled[i+offsetX][j+offsetY]) {
					validPixels.push_back(make_pair(i,j));
				}
			}
		}
	}
}

/*****************/
/* Synth Methods */
/*****************/

Synth::Synth(Image i, int patchSize) :
		sample(i), result(Image(sideLength, sideLength, 1, 3)), 
		patchSize{patchSize}
{
	sample.pixelsFilled =
		vector<vector<bool>>(sideLength, vector<bool>(sideLength, true));
}

void Synth::synthesize()
{
	if(!sanityChecks()) return;
	placeSeed();
	// Loop around seed, need to synthesize middle pixel in patch
	uint a = patchSize;
	uint b = 0;
	while (a < sideLength) {
		printf("a = %d, b = %d\n", a, b);
		assignColor(a,b);
		assignColor(b,a);
		b++;
		if (b == a) {
		        assignColor(a,a);
			a++;
			b=0;
		}
	}
}

bool Synth::sanityChecks()
{
	if(patchSize > sampleSideLength) {
		printf("Error patchsize %d is greater than sampleSize %d\n", patchSize, sampleSideLength);
		return false;
	}
	return true;
}
//Copies a randomly chosen seed patch from sample to (0,0) of result.
void Synth::placeSeed()
{
	srand(time(NULL));
	uint randX = rand() % (sampleSideLength - patchSize);
	uint randY = rand() % (sampleSideLength - patchSize);
	uint resZ = sideLength/2 - patchSize/2;

	cout << "randX: " << randX << endl;
	cout << "randY: " << randY << endl;

	Patch samplePatch = sample.getPatch(randX, randY, patchSize);
	Patch centerPatch = result.getPatch(0, 0, patchSize);
	centerPatch.copyPatch(samplePatch);
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
			float diff = res.difference(sam);
			if(diffs.size() <= 5) {
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
	for(int i = 0; i < 5; i++) {
		pair<float, pair<uint, uint>> candidate = diffs[i];
		similaritySum += 100.0 / candidate.first;
	}

	// Select patch with probability proportional to its similarity
	srand(time(NULL));
	float r = (float)rand() * (similaritySum / RAND_MAX);
	pair<float, pair<uint, uint>> chosenDiff;
	float similarity;
	for(int i = 0; i < 5; i++) {
		pair<float, pair<uint, uint>> candidate = diffs[i];
		similarity = 100.0 / candidate.first;
		if(r <= similarity) {
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
