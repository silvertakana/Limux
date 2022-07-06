#pragma once
#include <glad/glad.h>
#include "Limux/Renderer/Buffer.h"
namespace LMX
{
	class OpenGLBuffer : public Buffer
	{
	protected:
		GLuint m_RendererID = 0;
	public:
		OpenGLBuffer() = default;
		OpenGLBuffer(void* data, uint32_t size, GLenum usage = GL_DYNAMIC_DRAW);
		OpenGLBuffer(uint32_t size);
		virtual void Bind(GLenum type) const;
		virtual void UnBind(GLenum type) const;
		
		virtual uint32_t GetRendererID() const override { return m_RendererID; }
		operator GLuint&() { return m_RendererID; }
		virtual ~OpenGLBuffer();
	};

	class OpenGLVertexBuffer : public OpenGLBuffer, public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(uint32_t size) : OpenGLBuffer(nullptr, size, GL_DYNAMIC_DRAW) {}
		OpenGLVertexBuffer(void* data, uint32_t size) : OpenGLBuffer(data, size, GL_STATIC_DRAW) {}
		virtual void Bind() const override { OpenGLBuffer::Bind(GL_VERTEX_ARRAY); };
		virtual void UnBind() const override{ OpenGLBuffer::UnBind(GL_VERTEX_ARRAY); };
		virtual uint32_t GetRendererID() const override { return OpenGLBuffer::GetRendererID(); }
		virtual void SetData(const void* data, uint32_t size) override;
	};
	
	class OpenGLIndexBuffer : public OpenGLBuffer, public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(void* data, uint32_t count) : OpenGLBuffer(data, count) {}
		virtual void Bind() const override { OpenGLBuffer::Bind(GL_ELEMENT_ARRAY_BUFFER); };
		virtual void UnBind() const override { OpenGLBuffer::UnBind(GL_ELEMENT_ARRAY_BUFFER); };
		virtual uint32_t GetRendererID() const override { return OpenGLBuffer::GetRendererID(); }
	};
}