#include "RenderingObject.h"
#include "Shape.h"

Shape::Shape(GLint size, GLsizei vertexCount,
			 const RenderingObject::Vertex *vertex,
			 GLsizei indexcount = 0, const GLuint *index = NULL)
	: object(new RenderingObject(size, vertexCount, vertex, indexcount, index)),
	  vertexCount(vertexCount)
{
}

void Shape::Draw() const
{
	object->bind();
	Execute();
}
void Shape::Execute() const
{
	glDrawArrays(GL_LINE_LOOP, 0, vertexCount);
}