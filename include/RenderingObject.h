#pragma once
#include <GL/glew.h>

class RenderingObject
{
	GLuint vao;
	GLuint vbo;

public:
	struct Vertex
	{
		GLfloat position[2];
		// GLfloat color[3];
	};
	RenderingObject(GLint size, GLsizei vertexCount, const Vertex *vertex)
	{
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex),
					 vertex, GL_STATIC_DRAW);

		glVertexAttribPointer(0, size, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
	}
	virtual ~RenderingObject()
	{
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &vbo);
	}

private:
	RenderingObject(const RenderingObject &o);
	RenderingObject &operator=(const RenderingObject &o);

public:
	void bind() const
	{
		glBindVertexArray(vao);
	}
};
