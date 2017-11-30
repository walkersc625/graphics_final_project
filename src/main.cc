#include <GL/glew.h>
#include <dirent.h>
#include <GLFW/glfw3.h>

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <glm/gtx/component_wise.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/io.hpp>
#include <debuggl.h>

#include "Texture.h"
#include "arg_util.h"

#include <CImg/CImg.h>

#define MAX_ARG_LENGTH 100

using namespace cimg_library;

int main(int argc, char* argv[])
{
	/* parse argument */
	if (argv[1] == NULL) {
		printf("ERROR: Texture name required.\n");
		return 0;
	}

	char filepath[MAX_ARG_LENGTH];
	if(!parse_args(argv[1], filepath)) {
		printf("ERROR: Invalid texture name.\n");
		return 0;
	}


	/* synthesize texture */
	Image i = Image(filepath);
	Synth synth(i, 3);
	synth.synthesize();

	/* display sample and result images */
	CImgDisplay result_disp(synth.result.image,"Result texture");
	CImgDisplay sample_disp(synth.sample.image,"Sample texture");

	/* poll for mouse or keyboard interrupts */
	while (!sample_disp.is_closed() || !result_disp.is_closed()) {
		// mouse and keyboard events?
    }

	return 0;
}