#include "ShapeIndex.h"

#include <iostream>

ShapeIndex::ShapeIndex(GLint size, GLsizei vertexCount, const RenderingObject::Vertex *vertex,
					   GLsizei indexCount, const GLuint *index)
	: Shape(size, vertexCount, vertex, indexCount, index),
	  indexCount(indexCount)
{
}
void ShapeIndex::Execute() const
{
	glDrawElements(GL_LINES, indexCount, GL_UNSIGNED_INT, 0);
}