#include <GL/glew.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <fstream>
#include <vector>
#include <iostream>
#include "ShaderCompiler.h"

bool readShaderSource(const char *name, std::vector<GLchar> &buffer)
{
	if (name == NULL)
		return false;
	std::ifstream file(name, std::ios::binary);
	if (file.fail())
	{
		std::cerr << "Error: Can't open shader source" << name << std::endl;
		return false;
	}
	file.seekg(0L, std::ios::end);
	GLsizei length = static_cast<GLsizei>(file.tellg());
	buffer.resize(length + 1);
	file.seekg(0L, std::ios::beg);
	file.read(buffer.data(), length);
	buffer[length] = '\0';
	if (file.fail())
	{
		std::cerr << "Error: Can't read shader source" << name << std::endl;
		file.close();
		return false;
	}
	file.close();
	return true;
}
GLuint PrepareShader(const char *vert, const char *frag)
{
	GLuint vertex_shader, fragment_shader, program;
	std::vector<GLchar> v_source, f_source;
	readShaderSource(vert, v_source);
	readShaderSource(frag, f_source);
	vertex_shader = CreateVertex(v_source.data());
	fragment_shader = CreateFragment(f_source.data());

	program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
	glLinkProgram(program);
	return program;
}
GLuint CreateVertex(const GLchar *source)
{
	GLuint s;
	s = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(s, 1, &source, NULL);
	glCompileShader(s);
	return s;
}
GLuint CreateFragment(const GLchar *source)
{
	GLuint s;
	s = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(s, 1, &source, NULL);
	glCompileShader(s);
	return s;
}