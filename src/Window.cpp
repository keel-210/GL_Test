#include "Window.h"

Window::Window(int width, int height, const char *title)
	: window(glfwCreateWindow(width, height, title, NULL, NULL)), scale(100.0f), CursorLocation{0.0f, 0.0f}
{
	if (!glfwInit())
		exit(EXIT_FAILURE);

	atexit(glfwTerminate);

	//後で調査 ver3.2以上にすると何も描画されない
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	// glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if (window == NULL)
	{
		std::cerr << "Can't create GLFW window." << std::endl;
		exit(1);
	}
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Can't initialize GLEW" << std::endl;
		exit(1);
	}
	glfwSwapInterval(1);
	glfwSetWindowUserPointer(window, this);

	glfwSetWindowSizeCallback(window, resize);
	resize(window, width, height);

	SetCallbacks(window);
}
Window::~Window()
{
	glfwDestroyWindow(window);
}
Window::operator bool()
{
	glfwWaitEvents();

	return !glfwWindowShouldClose(window);
}
void Window::swapBuffers() const
{
	glfwSwapBuffers(window);
}
void Window::resize(GLFWwindow *const window, int width, int height)
{
	int fbwidth, fbheight;
	glfwGetFramebufferSize(window, &fbwidth, &fbheight);

	glViewport(0, 0, fbwidth, fbheight);

	Window *const
		instance(static_cast<Window *>(glfwGetWindowUserPointer(window)));
	if (instance != NULL)
	{
		instance->size[0] = static_cast<GLfloat>(width);
		instance->size[1] = static_cast<GLfloat>(height);
	}
}
void Window::SetCallbacks(GLFWwindow *const window)
{
	glfwSetErrorCallback(error_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, Cursor_callback);
	glfwSetScrollCallback(window, Scroll_callback);
}
void Window::error_callback(int error, const char *description)
{
	fprintf(stderr, "Error: %s\n", description);
}

void Window::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	Window *const
		instance(static_cast<Window *>(glfwGetWindowUserPointer(window)));
	if (instance != NULL)
	{
		if (glfwGetKey(window, GLFW_KEY_LEFT) != GLFW_RELEASE)
			instance->CursorLocation[0] -= 2.0f / instance->size[0];
		if (glfwGetKey(window, GLFW_KEY_RIGHT) != GLFW_RELEASE)
			instance->CursorLocation[0] += 2.0f / instance->size[0];
		if (glfwGetKey(window, GLFW_KEY_DOWN) != GLFW_RELEASE)
			instance->CursorLocation[1] -= 2.0f / instance->size[1];
		if (glfwGetKey(window, GLFW_KEY_UP) != GLFW_RELEASE)
			instance->CursorLocation[1] += 2.0f / instance->size[1];
	}
}
void Window::Cursor_callback(GLFWwindow *window, double xpos, double ypos)
{
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) != GLFW_RELEASE)
	{
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		Window *const
			instance(static_cast<Window *>(glfwGetWindowUserPointer(window)));
		if (instance != NULL)
		{
			instance->CursorLocation[0] = static_cast<GLfloat>(x) * 2.0f / instance->size[0] - 1.0f;
			instance->CursorLocation[1] = 1.0f - static_cast<GLfloat>(y) * 2.0f / instance->size[1];
		}
	}
}
void Window::Scroll_callback(GLFWwindow *window, double x, double y)
{
	Window *const
		instance(static_cast<Window *>(glfwGetWindowUserPointer(window)));
	if (instance != NULL)
	{
		instance->scale += static_cast<GLfloat>(y);
	}
}