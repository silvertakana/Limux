#include "lmxpch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace LMX
{
	Ref<VertexBuffer> VertexBuffer::Create(void* data, uint32_t size)
	{
		Ref<VertexBuffer> buffer = nullptr;
		SWITCHRENDERERAPI(
			buffer.reset((VertexBuffer*)new OpenGLVertexBuffer(data, size));
		);
		buffer->Size = size;
		return buffer;
	}
	Ref<IndexBuffer> IndexBuffer::Create(void* data, uint32_t size)
	{
		Ref<LMX::IndexBuffer> buffer = nullptr;
		SWITCHRENDERERAPI(
			buffer.reset((IndexBuffer*)new OpenGLIndexBuffer(data, size));
		);
		buffer->Size = size;
		return buffer;
	}
}