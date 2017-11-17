#include "Texture.h"
#include <iostream>
#include <string>
#include <jpegio.h>

using namespace std;

Texture::Texture(const string filepath)
{
	if (!LoadJPEG(filepath, &image)) {
		cout << "load image failed\n";
	} else {
		printf("image width: %d\n", image.width);
		printf("image height: %d\n", image.height);
	}
}