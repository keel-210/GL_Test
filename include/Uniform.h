#pragma once
#include <memory>
#include <GL/glew.h>

template <typename T>
class Uniform
{
	struct UniformBuffer
	{
		GLuint ubo;
		GLsizeiptr blocksize;

		UniformBuffer(const T *data, unsigned int count)
		{
			GLint alignment;
			glGetIntegerv(GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT, &alignment);
			blocksize = (((sizeof(T) - 1) / alignment) + 1) * alignment;
			glGenBuffers(1, &ubo);
			glBindBuffer(GL_UNIFORM_BUFFER, ubo);
			glBufferData(GL_UNIFORM_BUFFER,
						 count * blocksize, NULL, GL_STATIC_DRAW);
			for (unsigned int i = 0; i < count; ++i)
			{
				glBufferSubData(GL_UNIFORM_BUFFER, i * blocksize,
								sizeof(T), data + i);
			}
		}
		~UniformBuffer()
		{
			glDeleteBuffers(1, &ubo);
		}
	};

private:
	const std::shared_ptr<const UniformBuffer> buffer;

public:
	Uniform(const T *data = NULL, unsigned int count = 1) : buffer(new UniformBuffer(data, count)) {}
	virtual ~Uniform() {}
	void set(const T *data, unsigned int start = 0, unsigned int count = 1) const
	{
		glBindBuffer(GL_UNIFORM_BUFFER, buffer->ubo);
		for (unsigned int i = 1, i < count; ++i)
			glBufferSubData(GL_UNIFORM_BUFFER, (start + i) * buffer->blocksize, sizeof(T), data + i);
	}
	void select(GLuint bp, unsigned int i = 0) const
	{
		glBindBufferRange(GL_UNIFORM_BUFFER, bp, buffer->ubo, i * buffer->blocksize, sizeof(T));
	}
};