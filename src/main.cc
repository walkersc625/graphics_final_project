#include <GL/glew.h>
#include <dirent.h>
#include <GLFW/glfw3.h>

#include <image.h>

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
#include <jpegio.h>

#include "Window.h"
#include "Texture.h"

using namespace std;
using namespace glm;

void ErrorCallback(int error, const char* description)
{
	std::cerr << "GLFW Error: " << description << "\n";
}

int main(int argc, char* argv[])
{
	Window w = Window();
	glfwSetErrorCallback(ErrorCallback);

	Texture t = Texture("../assets/diagonals.jpg");
	//glDrawPixels(t.image.width, t.image.height, GL_RGB, GL_UNSIGNED_BYTE, (void*) t.image.bytes.data());

	//create canvas geometry
	vector<vec4> corners;
	corners.push_back(vec4(-1, 1, 0, 0));
	corners.push_back(vec4(1, 1, 0, 0));
	corners.push_back(vec4(1, -1, 0, 0));
	corners.push_back(vec4(-1, -1, 0, 0));

	uvec4 indices = uvec4(0, 1, 2, 3);

	

	while (!glfwWindowShouldClose(w.glWindow)) {
		int width = w.width;
		int height = w.height;

		// Setup some basic window stuff.
		glfwGetFramebufferSize(w.glWindow, &width, &height);
		glViewport(0, 0, width, height);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_MULTISAMPLE);
		glEnable(GL_BLEND);
		glEnable(GL_CULL_FACE);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDepthFunc(GL_LESS);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glCullFace(GL_BACK);

		glfwPollEvents();
		//glfwSwapBuffers(w.glWindow);
	}
	glfwDestroyWindow(w.glWindow);
	glfwTerminate();

	return 0;
}