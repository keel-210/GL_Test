#include <GL/glew.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "linmath.h"
#include "ShaderCompiler.h"
#include "Shape.h"
#include "Window.h"
#include "Matrix.h"
#include "ShapeIndex.h"
#include "MeshShape.h"
#include "SolidShape.h"
#include "TestConst.h"

#include <cstdlib>
#include <memory>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

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
	//Windowコンストラクタの前にGLFWを初期化しなければならない←どうにかしろ美しくないだろうが
	//イニシャライザとコンストラクタの順番変えられない以上どうにも
	Window window;

	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glfwSetTime(0.0);

	std::unique_ptr<const Shape> shape(new MeshShape(3, 36, SolidColorCubeVertex, 36, SolidColorCubeIndex));

	GLuint program = PrepareShader("test.vert", "test.frag");
	const GLint projectionLoc(glGetUniformLocation(program, "projection"));
	const GLint modleviewLoc(glGetUniformLocation(program, "modelview"));

	while (window)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(program);

		const GLfloat *const size(window.GetSize());
		const GLfloat fovy(window.GetScale() * 0.01f);
		const GLfloat aspect(size[0] / size[1]);
		const Matrix projection(Matrix::Perspective(fovy, aspect, 1.0f, 10.0f));
		//モデル変換行列
		const GLfloat *const location(window.GetLocation());
		const Matrix r(Matrix::Rotate(static_cast<GLfloat>(glfwGetTime() * 5.0f), 1.0f, 1.0f, -1.0f));
		const Matrix model(Matrix::Translate(location[0], location[1], 0.0f) * r);
		//ビュー変換行列
		const Matrix view(Matrix::LookAt(3.0f, 4.0f, 5.0f,
										 0.0f, 0.0f, 0.0f,
										 0.0f, 1.0f, 0.0f));
		//モデルビュー変換行列
		const Matrix modelview(view * model);

		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, projection.data());
		glUniformMatrix4fv(modleviewLoc, 1, GL_FALSE, modelview.data());
		shape->Draw();

		const Matrix modelview1(modelview * Matrix::Translate(0.0f, 0.0f, 3.0f));
		glUniformMatrix4fv(modleviewLoc, 1, GL_FALSE, modelview1.data());
		shape->Draw();

		window.swapBuffers();
		glfwPollEvents();
	}
	exit(EXIT_SUCCESS);
}
