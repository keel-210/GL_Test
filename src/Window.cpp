#include "Window.h"

Window::Window(int width, int height, const char *title)
	: window(glfwCreateWindow(width, height, title, NULL, NULL)), scale(100.0f), CursorLocation{0.0f, 0.0f}
{
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
}
Window::~Window()
{
	glfwDestroyWindow(window);
}
Window::operator bool()
{
	glfwWaitEvents();

	//これよくない
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
