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
		cout << "image loaded successfully\n";
		printf("\timage width: %d\n", image.width);
		printf("\timage height: %d\n", image.height);
	}
}