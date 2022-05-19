#include "lmxpch.h"
#include "VertexArray.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "Renderer.h"
namespace LMX
{
	VertexArray* LMX::VertexArray::Create(const LMX::Ref<VertexBuffer>& VBO, const LMX::Ref<IndexBuffer>& EBO, uint32_t offset, uint32_t stride)
	{
		VertexArray* VAO = nullptr;
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL:
			VAO = new OpenGLVertexArray(VBO, EBO, offset, stride);
			break;
		default:
			LMX_ASSERT(false, "Unknown RendererAPI!");
			break;
		}
		return VAO;
	}
}
