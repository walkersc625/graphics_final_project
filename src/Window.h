#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <GLFW/glfw3.h>

using namespace std;
using namespace glm;

class Window
{
	

	void init_glefw();

	public:

		//initialized in constructor
		GLFWwindow *glWindow;

		int width = 800;
		int height = 600;
		string title = "Texture";

		Window();
		//~Window();
};

#endif