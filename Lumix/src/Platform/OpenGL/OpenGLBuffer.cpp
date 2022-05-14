#include "lmxpch.h"

#include "OpenGLBuffer.h"


namespace LMX
{
	OpenGLBuffer::OpenGLBuffer(void* data, uint32_t size)
	{
		glCreateBuffers(1, &ID);
		glNamedBufferData(ID, size, data, GL_STATIC_DRAW);
	}
	void OpenGLBuffer::Bind(GLenum type) const
	{
		glBindBuffer(type, ID);
	}
	void OpenGLBuffer::UnBind(GLenum type) const
	{
		glBindBuffer(type, 0);
	}
	OpenGLBuffer::~OpenGLBuffer()
	{
		glDeleteBuffers(1, &ID);
	}
}