#pragma once

#include "Shape.h"

class ShapeIndex : public Shape
{
protected:
	const GLsizei indexCount;

public:
	ShapeIndex(GLint size, GLsizei vertexCount, const RenderingObject::Vertex *vertex,
			   GLsizei indexCount, const GLuint *index);
	virtual void Execute() const;
};