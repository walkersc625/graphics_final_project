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
	delete (synth);
}

//handlers
//http://cimg.eu/reference/structcimg__library_1_1CImgDisplay.html

int main(int argc, char* argv[])
{
	/* command line arguments */
	char* textureName = argv[1];
	char* patchSize = argv[2];
	char* sizeFlag = argv[3];
	char filepath[MAX_ARG_LENGTH];

	Image i;
	Synth* synth;
	bool small;

	if (argc == 2) {
		/* wrong number of arguments present */
		printf("ERROR: Texture name and patch size required.\n");
		return 0;

	} else if (textureName != nullptr && patchSize != nullptr) {

		/* use command line arguments (both are valid) */
		if(!parse_args(textureName, sizeFlag, filepath)) {
			return 0;
		}
		small = (sizeFlag != nullptr && !strcmp(sizeFlag, "-s"));
		i = Image(filepath);
		synth = new Synth(i, atoi(patchSize), small, 0);

	} else if (argc == 1) {

		/* use GUI (No command line arguments) */
		GUI* gui = new GUI();
		char* fp = gui->run();

		/* get information from GUI */
		strcpy(filepath, fp);
		int patchSizeValue = gui->patchSizeSlider->value();
		if (patchSizeValue % 2 == 0) {
			patchSizeValue++;
		}

		int resultSizeValue = gui->resultSizeSlider->value();
		if (patchSizeValue > resultSizeValue) {
			patchSizeValue = 127;
		}


		i = Image(filepath);
		synth = new Synth(i, patchSizeValue, false, resultSizeValue);

	}


	/* synthesize texture */
    thread synthThread(runProgram, synth);

	/* display sample and result images */
	CImgDisplay result_disp(synth->result.image,"Result texture");
	CImgDisplay sample_disp(synth->sample.image,"Sample texture");

	/* poll for mouse or keyboard interrupts */
	while (!sample_disp.is_closed() || !result_disp.is_closed()) {
		result_disp.display(synth->result.image);
    }

	return 0;
}
