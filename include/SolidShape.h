#pragma once

#include "Shape.h"

class SolidShape : public Shape
{
public:
	SolidShape(GLint size, GLsizei vertexCount, const RenderingObject::Vertex *vertex,
			   GLsizei indexCount, const GLuint *index);
	virtual void Execute() const;
};