#pragma once

#include "Shape.h"

class MeshShape : public Shape
{
protected:
	const GLsizei indexCount;

public:
	MeshShape(GLint size, GLsizei vertexCount, const RenderingObject::Vertex *vertex,
			  GLsizei indexCount, const GLuint *index);
	virtual void Execute() const;
};