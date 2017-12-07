#include <GL/glew.h>
#include <dirent.h>
#include <GLFW/glfw3.h>

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>

#include <glm/gtx/component_wise.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/io.hpp>
#include <debuggl.h>
#include <thread>

#include "Texture.h"
#include "arg_util.h"
#include "GUI.h"

#include <CImg/CImg.h>

#define MAX_ARG_LENGTH 100

using namespace std;
using namespace cimg_library;

void runProgram(Synth* synth) {
	synth->synthesize();
	printf("Done!");
}

//handlers
//http://cimg.eu/reference/structcimg__library_1_1CImgDisplay.html

int main(int argc, char* argv[])
{
	char* textureName = argv[1];
	char* patchSize = argv[2];
	char* sizeFlag = argv[3];

	/* parse argument */
	if (textureName == NULL || patchSize == NULL) {
		printf("ERROR: Texture name and patch size required.\n");
		return 0;
	}

	char filepath[MAX_ARG_LENGTH];
	if(!parse_args(textureName, sizeFlag, filepath)) {
		return 0;
	}

	/* GUI stuff */
	GUI* gui = new GUI();
	gui->run();


	/* synthesize texture */
	Image i = Image(filepath);

	// Have patchsize always be odd for simplicity
	Synth synth(i, atoi(argv[2]));
    thread synthThread(runProgram, &synth);

	/* display sample and result images */
	CImgDisplay result_disp(synth.result.image,"Result texture");
	CImgDisplay sample_disp(synth.sample.image,"Sample texture");

	/* poll for mouse or keyboard interrupts */
	while (!sample_disp.is_closed() || !result_disp.is_closed()) {
		result_disp.display(synth.result.image);
    }

	return 0;
}
