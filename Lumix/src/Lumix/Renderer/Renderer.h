#pragma once
#include "RenderCommand.h"
#include "Shader.h"
#include "Camera.h"
#include "glm/glm.hpp"
namespace LMX
{

	class Renderer
	{
	public:
		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
	};


}