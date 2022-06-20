#pragma once
#include "Buffer.h"
#include "VertexArray.h"
#include "Vertex.h"
#include "Texture.h"
#include "Shader.h"
namespace LMX
{
	class Mesh
	{
	protected:
		bool m_IsInit = false;
	public:
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Ref<Texture>> textures;

		
		Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Ref<Texture>> textures);
		void Draw(Ref<Shader> shader, const glm::mat4& offset = glm::mat4{1.f});
		void Init();
	private:
		Ref<VertexArray> m_vertexArray;
	};
}

