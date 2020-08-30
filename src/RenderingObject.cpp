#include "RenderingObject.h"

RenderingObject::RenderingObject(GLint size, GLsizei vertexCount, const Vertex *vertex)
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
RenderingObject::~RenderingObject()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
}

void RenderingObject::bind() const
{
	glBindVertexArray(vao);
}
