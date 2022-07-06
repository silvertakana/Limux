#include "lmxpch.h"
#include "Renderer.h"
#include "Vertex.h"
namespace LMX
{
	Scope<Renderer::SceneData> Renderer::s_SceneData = CreateScope<Renderer::SceneData>();
	Ref<Renderer::Statistics> Renderer::s_Statistics = CreateRef<Renderer::Statistics>();
	
	void Renderer::BeginScene()
	{
		LMX_PROFILE_FUNCTION();
		(*s_Statistics) = {};
	}

	Ref<Renderer::Statistics> Renderer::EndScene()
	{
		LMX_PROFILE_FUNCTION();
		return s_Statistics;
	}
	
	void Renderer::Init()
	{
		LMX_PROFILE_FUNCTION();
		RenderCommand::Init();
	}
	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		LMX_PROFILE_FUNCTION();
		RenderCommand::SetViewport(0, 0, width, height);
	}
	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		LMX_PROFILE_FUNCTION();
		shader->Bind();
		shader->SetUniform("u_Transform", transform);
		
		s_Statistics->DrawCalls++;
		
		size_t indexCount = vertexArray->GetEBO()->GetSize();
		s_Statistics->IndexCount += indexCount;
		size_t vertexCount = vertexArray->GetVBO()->GetSize() / sizeof(Vertex);
		s_Statistics->VertexCount += vertexCount;
		
		s_Statistics->triangleCount += indexCount/3.f;
		
		
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}