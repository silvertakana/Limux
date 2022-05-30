#include "lmxpch.h"

#include "OpenGLBuffer.h"


namespace LMX
{
	OpenGLBuffer::OpenGLBuffer(void* data, uint32_t size)
	{
		LMX_PROFILE_FUNCTION();
		glCreateBuffers(1, &ID);
		glNamedBufferData(ID, size, data, GL_STATIC_DRAW);
	}
	void OpenGLBuffer::Bind(GLenum type) const
	{
		LMX_PROFILE_FUNCTION();
		glBindBuffer(type, ID);
	}
	void OpenGLBuffer::UnBind(GLenum type) const
	{
		LMX_PROFILE_FUNCTION();
		glBindBuffer(type, 0);
	}
	OpenGLBuffer::~OpenGLBuffer()
	{
		LMX_PROFILE_FUNCTION();
		glDeleteBuffers(1, &ID);
	}
}