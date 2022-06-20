#include "lmxpch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace LMX
{
	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		LMX_PROFILE_FUNCTION();
		Ref<VertexBuffer> buffer = nullptr;
		LMX_SWITCHRENDERERAPI(
			buffer.reset((VertexBuffer*)new OpenGLVertexBuffer(size));
		);
		buffer->Size = size;
		return buffer;
	}
	Ref<VertexBuffer> VertexBuffer::Create(void* data, uint32_t size)
	{
		LMX_PROFILE_FUNCTION();
		Ref<VertexBuffer> buffer = nullptr;
		LMX_SWITCHRENDERERAPI(
			buffer.reset((VertexBuffer*)new OpenGLVertexBuffer(data, size));
		);
		buffer->Size = size;
		return buffer;
	}
	Ref<IndexBuffer> IndexBuffer::Create(void* data, uint32_t size)
	{
		LMX_PROFILE_FUNCTION();
		Ref<LMX::IndexBuffer> buffer = nullptr;
		LMX_SWITCHRENDERERAPI(
			buffer.reset((IndexBuffer*)new OpenGLIndexBuffer(data, size));
		);
		buffer->Size = size;
		return buffer;
	}
}