#include "RenderingObject.h"
#include <stdio.h>

RenderingObject::RenderingObject(GLint size, GLsizei vertexCount, const Vertex *vertex,
								 GLsizei indexcount = 0, const GLuint *index = NULL)
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex),
				 vertex, GL_STATIC_DRAW);

	glVertexAttribPointer(0, size, GL_FLOAT, GL_FALSE,
						  sizeof(Vertex), static_cast<Vertex *>(0)->position);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
						  sizeof(Vertex), static_cast<Vertex *>(0)->normal);
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
				 indexcount * sizeof(GLuint), index, GL_STATIC_DRAW);
}
RenderingObject::~RenderingObject()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
}

void RenderingObject::bind() const
{
	glBindVertexArray(vao);
}
