#pragma once
#include <GL/glew.h>

class RenderingObject
{
	//Vertex Array Object
	GLuint vao;
	//Vertex Buffer Object
	GLuint vbo;
	//Index Buffer Object
	GLuint ibo;

public:
	struct Vertex
	{
		GLfloat position[3];
		GLfloat color[3];
	};
	RenderingObject(GLint size, GLsizei vertexCount, const Vertex *vertex,
					GLsizei indexcount, const GLuint *index);
	virtual ~RenderingObject();
	void bind() const;

private:
	RenderingObject(const RenderingObject &o);
	RenderingObject &operator=(const RenderingObject &o);
};
