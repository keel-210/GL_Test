#include <GL/glew.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "linmath.h"
#include "ShaderCompiler.h"
#include "Shape.h"
#include "Window.h"
#include "Matrix.h"

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
	//WindowのメンバイニシャライザによってglfwCreateWindowが呼ばれるので
	//Windowコンストラクタの前にGLFWを初期化しなければならない←どうにかしろ
	//イニシャライザとコンストラクタの順番変えられない以上どうにも
	Window window;

	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	std::unique_ptr<const Shape> shape(new Shape(2, 4, RenderingVertex));

	GLuint program = PrepareShader("test.vert", "test.frag");
	const GLint projectionLoc(glGetUniformLocation(program, "projection"));
	const GLint modleviewLoc(glGetUniformLocation(program, "modelview"));

	while (window)
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(program);

		// //Scale変換行列
		// const GLfloat *const size(window.GetSize());
		// const GLfloat scale(window.GetScale() * 2.0f);
		// const Matrix scaling(Matrix::Scale(scale / size[0], scale / size[1], 1.0f));
		// //Translate変換行列
		// const GLfloat *const position(window.GetLocation());
		// const Matrix translation(Matrix::Translate(position[0], position[1], 0.0f));
		// //モデル変換行列
		// const Matrix model(translation * scaling);
		// //ビュー変換行列
		// const Matrix view(Matrix::LookAt(0.0f, 0.0f, 0.0f,
		// 								 -1.0f, -1.0f, -1.0f,
		// 								 0.0f, 1.0f, 0.0f));
		//直交投影変換行列
		const GLfloat *const size(window.GetSize());
		const GLfloat scale(window.GetScale() * 2.0f);
		const GLfloat w(size[0] / scale), h(size[1] / scale);
		const Matrix projection(Matrix::Orthogonal(-w, w, -h, h, 1.0f, 10.0f));
		//モデル変換行列
		const GLfloat *const location(window.GetLocation());
		const Matrix model(Matrix::Translate(location[0], location[1], 0.0f));
		//ビュー変換行列
		const Matrix view(Matrix::LookAt(3.0f, 4.0f, 5.0f,
										 0.0f, 0.0f, 0.0f,
										 0.0f, 1.0f, 0.0f));
		//モデルビュー変換行列
		const Matrix modelview(view * model);

		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, projection.data());
		glUniformMatrix4fv(modleviewLoc, 1, GL_FALSE, modelview.data());

		shape->Draw();
		window.swapBuffers();
		glfwPollEvents();
	}
	exit(EXIT_SUCCESS);
}
