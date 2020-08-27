#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window
{
public:
	GLFWwindow *const window;
	GLfloat scale;
	GLfloat size[2];
	GLfloat CursorLocation[2];

	Window(int width = 640, int height = 480, const char *title = "Hello!");
	virtual ~Window();
	explicit operator bool();
	void swapBuffers() const;
	static void resize(GLFWwindow *const window, int width, int height);
	void SetCallbacks(GLFWwindow *const window);
	static void error_callback(int error, const char *description);
	static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
	static void Cursor_callback(GLFWwindow *window, double xpos, double ypos);
	static void Scroll_callback(GLFWwindow *window, double xpos, double ypos);

	GLfloat GetScale() const { return scale; }
	const GLfloat *GetSize() const { return size; }
	const GLfloat *GetLocation() const { return CursorLocation; }
};