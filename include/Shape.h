#pragma once
#include <memory>

#include "RenderingObject.h"

class Shape
{
	std::shared_ptr<const RenderingObject> object;

protected:
	const GLsizei vertexCount;

public:
	Shape(GLint size, GLsizei vertexCount,
		  const RenderingObject::Vertex *vertex,
		  GLsizei indexcount, const GLuint *index);
	void Draw() const;
	virtual void Execute() const;
};