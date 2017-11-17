#ifndef TEXTURE_H
#define TEXTURE_H

#include <vector>
#include <string>

#include <image.h>
#include <GL/glew.h>

using namespace std;

struct Texture {
	Image image;
	GLuint id;

	Texture(const string filepath);
};

#endif