#include "MeshShape.h"

MeshShape::MeshShape(GLint size, GLsizei vertexCount, const RenderingObject::Vertex *vertex,
					 GLsizei indexCount, const GLuint *index)
	: Shape(size, vertexCount, vertex, indexCount, index),
	  indexCount(indexCount)
{
}
void MeshShape::Execute() const
{
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
}