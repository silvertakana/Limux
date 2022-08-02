#include "lmxpch.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include "Mesh.h"
#include "Renderer.h"


namespace LMX
{
	Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
	{
		LMX_PROFILE_FUNCTION();
		this->vertices = vertices;
		this->indices = indices;
	}
	void Mesh::Draw(Ref<Shader> shader, const glm::mat4& offset)
	{
		LMX_PROFILE_FUNCTION();
		if (!m_IsInit)
			Init();
		
		LMX::Renderer::Submit(shader, m_vertexArray, offset);
	}
	
	void Mesh::Init()
	{
		LMX_PROFILE_FUNCTION();
		if (!m_IsInit)
		{
			LMX::Ref<LMX::VertexBuffer> VBO;
			VBO = LMX::VertexBuffer::Create(vertices.data(), vertices.size() * sizeof(LMX::Vertex));
			LMX::Ref<LMX::IndexBuffer> EBO;
			EBO = LMX::IndexBuffer::Create(indices.data(), indices.size() * sizeof(uint32_t));

			m_vertexArray = LMX::VertexArray::Create(VBO, EBO, 0, sizeof(LMX::Vertex));
			m_vertexArray->AddAttrib(LMX::DataType::Float3, true, offsetof(LMX::Vertex, Position));
			m_vertexArray->AddAttrib(LMX::DataType::Float3, true, offsetof(LMX::Vertex, Normal));
			m_vertexArray->AddAttrib(LMX::DataType::Float2, true, offsetof(LMX::Vertex, TexCoord));
			m_vertexArray->AddAttrib(LMX::DataType::Float4, true, offsetof(LMX::Vertex, Color));

			m_IsInit = true;
		}
	}
}