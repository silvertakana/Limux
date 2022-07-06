#include "lmxpch.h"

#include "OpenGLBuffer.h"


namespace LMX
{
	OpenGLBuffer::OpenGLBuffer(void* data, uint32_t size, GLenum usage)
	{
		LMX_PROFILE_FUNCTION();
		glCreateBuffers(1, &m_RendererID);
		glNamedBufferData(m_RendererID, size, data, usage);
	}
	OpenGLBuffer::OpenGLBuffer(uint32_t size)
	{}
	void OpenGLBuffer::Bind(GLenum type) const
	{
		LMX_PROFILE_FUNCTION();
		glBindBuffer(type, m_RendererID);
	}
	void OpenGLBuffer::UnBind(GLenum type) const
	{
		LMX_PROFILE_FUNCTION();
		glBindBuffer(type, 0);
	}
	
	void OpenGLVertexBuffer::SetData(const void* data, uint32_t size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}
	
	OpenGLBuffer::~OpenGLBuffer()
	{
		LMX_PROFILE_FUNCTION();
		glDeleteBuffers(1, &m_RendererID);
	}
}