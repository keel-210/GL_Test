#include <GL/glew.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "linmath.h"
#include "ShaderCompiler.h"
#include "Shape.h"
#include "Window.h"

#include <cstdlib>
#include <memory>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

constexpr RenderingObject::Vertex RenderingVertex[] = {
	{-0.5f, -0.5f},
	{0.5f, -0.5f},
	{0.5f, 0.5},
	{-0.5f, 0.5f}};

static void error_callback(int error, const char *description)
{
	fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void InitializeGLFW()
{
	if (!glfwInit())
		exit(EXIT_FAILURE);

	atexit(glfwTerminate);

	//後で調査 ver3.2以上にすると何も描画されない
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	// glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}
int mainLoop(void)
{
	InitializeGLFW();
	Window window;

	glfwSetErrorCallback(error_callback);
	glfwSetKeyCallback(window.window, key_callback);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	std::unique_ptr<const Shape> shape(new Shape(2, 4, RenderingVertex));

	GLuint program = PrepareShader("test.vert", "test.frag");
	const GLint sizeLoc(glGetUniformLocation(program, "size"));
	const GLint scaleLoc(glGetUniformLocation(program, "scale"));

	while (window)
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(program);
		glUniform2fv(sizeLoc, 1, window.GetSize());
		glUniform1f(scaleLoc, window.GetScale());

		shape->Draw();
		window.swapBuffers();
		glfwPollEvents();
	}

	exit(EXIT_SUCCESS);
}
