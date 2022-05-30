#include "lmxpch.h"
#include "VertexArray.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "Renderer.h"
namespace LMX
{
	Ref<VertexArray> LMX::VertexArray::Create(const LMX::Ref<VertexBuffer>& VBO, const LMX::Ref<IndexBuffer>& EBO, uint32_t offset, uint32_t stride)
	{
		LMX_PROFILE_FUNCTION();
		LMX_SWITCHRENDERERAPI(
			return CreateRef<OpenGLVertexArray>(VBO, EBO, offset, stride);
		);
		return nullptr;
	}
}
