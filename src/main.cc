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

using namespace std;
using namespace glm;

void ErrorCallback(int error, const char* description)
{
	std::cerr << "GLFW Error: " << description << "\n";
}

int main(int argc, char* argv[])
{
	glfwSetErrorCallback(ErrorCallback);
	return 0;
}