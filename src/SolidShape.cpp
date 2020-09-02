#include "SolidShape.h"

SolidShape::SolidShape(GLint size, GLsizei vertexCount, const RenderingObject::Vertex *vertex,
					   GLsizei indexcount, const GLuint *index)
	: Shape(size, vertexCount, vertex, indexcount, index) {}

void SolidShape::Execute() const
{
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}