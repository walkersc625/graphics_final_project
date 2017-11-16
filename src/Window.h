#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <dirent.h>

#include <image.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <glm/gtx/component_wise.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/io.hpp>
#include <debuggl.h>
#include "util.h"

using namespace std;
using namespace glm;

class Window
{
	int width = 800;
	int height = 600;
	string title = "Texture";

	//initialized in constructor
	GLFWwindow *glWindow;

	void init_glefw();

	public:

		Window() { init_glefw() };
		~Window();
};

#endif