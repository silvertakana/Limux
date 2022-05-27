#include "lmxpch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace LMX
{
	VertexBuffer* VertexBuffer::Create(void* data, uint32_t size)
	{
		LMX::VertexBuffer* buffer = nullptr;
		SWITCHRENDERERAPI(
			buffer = new OpenGLVertexBuffer(data, size);
		);
		buffer->Size = size;
		return buffer;
	}
	IndexBuffer* IndexBuffer::Create(void* data, uint32_t size)
	{
		LMX::IndexBuffer* buffer = nullptr;
		SWITCHRENDERERAPI(
			buffer = new OpenGLIndexBuffer(data, size);
		);
		buffer->Size = size;
		return buffer;
	}
}