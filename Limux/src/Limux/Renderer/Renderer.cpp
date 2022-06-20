#include "lmxpch.h"
#include "Renderer.h"
namespace LMX
{
	Scope<Renderer::SceneData> Renderer::s_SceneData = CreateScope<Renderer::SceneData>();
	
	void Renderer::BeginScene()
	{
		LMX_PROFILE_FUNCTION();
	}

	void Renderer::EndScene()
	{
		LMX_PROFILE_FUNCTION();
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
		
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}