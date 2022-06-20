#pragma once
#include <glad/glad.h>
#include "Limux/Renderer/Buffer.h"
namespace LMX
{
	class OpenGLBuffer : public Buffer
	{
	public:
		GLuint ID = 0;
		OpenGLBuffer() = default;
		OpenGLBuffer(void* data, uint32_t size, GLenum usage = GL_DYNAMIC_DRAW);
		OpenGLBuffer(uint32_t size);
		virtual void Bind(GLenum type) const;
		virtual void UnBind(GLenum type) const;
		
		
		operator GLuint&() { return ID; }
		virtual ~OpenGLBuffer();
	};

	class OpenGLVertexBuffer : public OpenGLBuffer, public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(uint32_t size) : OpenGLBuffer(nullptr, size, GL_STATIC_DRAW) {}
		OpenGLVertexBuffer(void* data, uint32_t size) : OpenGLBuffer(data, size) {} 
		virtual void Bind() const override { OpenGLBuffer::Bind(GL_VERTEX_ARRAY); };
		virtual void UnBind() const override{ OpenGLBuffer::UnBind(GL_VERTEX_ARRAY); };
		virtual void SetData(const void* data, uint32_t size) override;
	};
	
	class OpenGLIndexBuffer : public OpenGLBuffer, public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(void* data, uint32_t size) : OpenGLBuffer(data, size) {}
		virtual void Bind() const override { OpenGLBuffer::Bind(GL_ELEMENT_ARRAY_BUFFER); };
		virtual void UnBind() const override { OpenGLBuffer::UnBind(GL_ELEMENT_ARRAY_BUFFER); };
	};
}