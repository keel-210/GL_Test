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

	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	std::unique_ptr<const Shape> shape(new Shape(2, 4, RenderingVertex));

	GLuint program = PrepareShader("test.vert", "test.frag");
	const GLint sizeLoc(glGetUniformLocation(program, "size"));
	const GLint scaleLoc(glGetUniformLocation(program, "scale"));
	const GLint locationLoc(glGetUniformLocation(program, "location"));

	while (window)
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(program);
		glUniform2fv(sizeLoc, 1, window.GetSize());
		glUniform1f(scaleLoc, window.GetScale());
		glUniform2fv(locationLoc, 1, window.GetLocation());

		shape->Draw();
		window.swapBuffers();
		glfwPollEvents();
	}

	exit(EXIT_SUCCESS);
}
