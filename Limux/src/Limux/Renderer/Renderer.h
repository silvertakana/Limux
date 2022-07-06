#pragma once
#include "RenderCommand.h"
#include "Shader.h"
#include "Camera/Camera.h"
#include "glm/glm.hpp"
namespace LMX
{

	class Renderer
	{
	public:
		struct Statistics
		{
			size_t DrawCalls = 0;
			size_t VertexCount = 0;
			size_t IndexCount = 0;
			size_t triangleCount = 0;
		};
		
		static void Init();
		static void OnWindowResize(uint32_t width, uint32_t height);
		
		static void BeginScene();
		static Ref<Statistics> EndScene();

		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
		};
		
		static Ref<Statistics> s_Statistics;
		static Scope<SceneData> s_SceneData;
	};


}