#include "lmxpch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace LMX
{
	VertexBuffer* VertexBuffer::Create(void* data, uint32_t size)
	{
		VertexBuffer* buffer = nullptr;
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL:
			buffer = new OpenGLVertexBuffer(data, size);
			break;
		default:
			LMX_ASSERT(false, "Unknown RendererAPI!");
			break;
		}
		buffer->Size = size;
		return buffer;
	}
	IndexBuffer* IndexBuffer::Create(void* data, uint32_t size)
	{
		IndexBuffer* buffer = nullptr;
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL:
			buffer = new OpenGLIndexBuffer(data, size);
			break;
		default:
			LMX_ASSERT(false, "Unknown RendererAPI!");
			break;
		}
		buffer->Size = size;
		return buffer;
	}
}