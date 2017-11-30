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

//#include "Window.h"
#include "Texture.h"
// #include "render_pass.h"

#include <CImg/CImg.h>

using namespace std;
using namespace glm;
using namespace cimg_library;

// const char* vertex_shader =
// #include "shaders/vertex_shader.vert"
// ;

// const char* geometry_shader =
// #include "shaders/geometry_shader.geom"
// ;

// const char* fragment_shader =
// #include "shaders/fragment_shader.frag"
// ;

// void ErrorCallback(int error, const char* description)
// {
// 	std::cerr << "GLFW Error: " << description << "\n";
// }

int main(int argc, char* argv[])
{
	Image i = Image("../assets/vintage.jpg");
	Synth synth(i, 3);
	synth.synthesize();
	CImgDisplay result_disp(synth.result.image,"Result texture");
	CImgDisplay sample_disp(synth.sample.image,"Sample texture");
	while (!sample_disp.is_closed() || !result_disp.is_closed()) {
		// mouse and keyboard events?
    }
	return 0;

	// Window w = Window();
	// glfwSetErrorCallback(ErrorCallback);

	// Texture t = Texture("../assets/vintage.jpg");
	// glGenTextures(1, &t.id);
	// glBindTexture(GL_TEXTURE_2D, t.id);
	// glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, t.image.width, t.image.height, 0, GL_RGB, GL_UNSIGNED_BYTE, t.image.bytes.data());
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// //create canvas geometry
	// vector<vec4> corners;
	// corners.push_back(vec4(-1.0f, 1.0f, 0.0f, 1.0f));	// Top left
	// corners.push_back(vec4(1.0f, 1.0f, 0.0f, 1.0f));	// Top right
	// corners.push_back(vec4(1.0f, -1.0f, 0.0f, 1.0f));	// Bot right
	// corners.push_back(vec4(-1.0f, -1.0f, 0.0f, 1.0f));	// Bot left

	// vector<uvec3> faces;
	// faces.push_back(uvec3(3,1,0));
	// faces.push_back(uvec3(1,3,2));

	// vector<vec2> uv_coords;
	// uv_coords.push_back(vec2(0, 0));
	// uv_coords.push_back(vec2(1, 0));
	// uv_coords.push_back(vec2(1, 1));
	// uv_coords.push_back(vec2(0, 1));

	// auto tex_data  = [t]() -> const void* {
	// 	return &t.id;
	// };

	// auto tex_binder = [t](int loc, const void* data) {
	// 	glUniform1i(loc, 0);
	// 	glActiveTexture(GL_TEXTURE0);
	//     glBindTexture(GL_TEXTURE_2D, *(GLuint*)data);
	// };

	// ShaderUniform texture_uniform = { "texture_sampler", tex_binder, tex_data };

	// RenderDataInput canvas_pass_input;
	// canvas_pass_input.assign(0, "vertex_position", corners.data(), corners.size(), 4, GL_FLOAT);
	// canvas_pass_input.assign(1, "vertex_uv", uv_coords.data(), uv_coords.size(), 2, GL_FLOAT);
	// canvas_pass_input.assign_index(faces.data(), faces.size(), 3);
	// RenderPass canvas_pass(
	// 	-1,
	// 	canvas_pass_input,
	// 	{vertex_shader, geometry_shader, fragment_shader},
	// 	{texture_uniform},
	// 	{"color"}
	// );

	// while (!glfwWindowShouldClose(w.glWindow)) {
	// 	int width = w.width;
	// 	int height = w.height;

	// 	// Setup some basic window stuff.
	// 	glfwGetFramebufferSize(w.glWindow, &width, &height);
	// 	glViewport(0, 0, width, height);
	// 	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	// 	glEnable(GL_DEPTH_TEST);
	// 	glEnable(GL_MULTISAMPLE);
	// 	glEnable(GL_BLEND);
	// 	glEnable(GL_CULL_FACE);
	// 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// 	glDepthFunc(GL_LESS);
	// 	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// 	glCullFace(GL_BACK);

	// 	canvas_pass.setup();
	// 	CHECK_GL_ERROR(glDrawElements(GL_TRIANGLES, faces.size()*3, GL_UNSIGNED_INT, 0));

	// 	glfwPollEvents();
	// 	glfwSwapBuffers(w.glWindow);
	// }
	// glfwDestroyWindow(w.glWindow);
	// glfwTerminate();

	return 0;
}