#include "lmxpch.h"
#include "VertexArray.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "Renderer.h"
namespace LMX
{
	VertexArray* LMX::VertexArray::Create(const LMX::Ref<VertexBuffer>& VBO, const LMX::Ref<IndexBuffer>& EBO, uint32_t offset, uint32_t stride)
	{
		SWITCHRENDERERAPI(
			return new OpenGLVertexArray(VBO, EBO, offset, stride);
		);
		return nullptr;
	}
}
