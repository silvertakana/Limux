#include "lmxpch.h"
#include "Renderer.h"
namespace LMX
{
	void Renderer::BeginScene()
	{}

	void Renderer::EndScene()
	{}
	
	void Renderer::Init()
	{
		RenderCommand::Init();
	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		shader->Bind();
		shader->setMat4("u_Transform", transform);
		
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}