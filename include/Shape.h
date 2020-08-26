#pragma once
#include <memory>

#include "RenderingObject.h"

class Shape
{
	std::shared_ptr<const RenderingObject> object;

protected:
	const GLsizei vertexCount;

public:
	Shape(GLint size, GLsizei vertexCount, const RenderingObject::Vertex *vertex)
		: object(new RenderingObject(size, vertexCount, vertex)), vertexCount(vertexCount)
	{
	}

	void Draw() const
	{
		object->bind();
		execute();
	}
	virtual void execute() const
	{
		glDrawArrays(GL_LINE_LOOP, 0, vertexCount);
	}
};