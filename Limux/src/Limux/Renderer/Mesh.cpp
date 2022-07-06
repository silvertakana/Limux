#include "lmxpch.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include "Mesh.h"
#include "Renderer.h"


namespace LMX
{
	Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Ref<Texture>> textures)
	{
		LMX_PROFILE_FUNCTION();
		this->vertices = vertices;
		this->indices = indices;
		this->textures = textures;
	}
	void Mesh::Draw(Ref<Shader> shader, const glm::mat4& offset)
	{
		LMX_PROFILE_FUNCTION();
		if (!m_IsInit)
			Init();
		shader->Bind();
		std::vector<std::string> textureNames; // set textures back to 0 (missing texture)
		std::map<Texture2D::TextureType, uint32_t> count;
		Texture2D::TextureType type;
		std::string stringType, identifier;
		
		textureNames.reserve(textures.size());
		for (int i = 0; i < textures.size(); i++)
		{
			LMX_PROFILE_SCOPE("Binding Textures");
			type = std::dynamic_pointer_cast<Texture2D>(textures[i])->type;
			stringType = Texture2D::TextureTypeToString(type);
			stringType[0] = std::toupper(stringType[0]);
			identifier = std::format("u_Texture_{0}{1}", stringType, count[type]++);
			shader->SetUniform(identifier, i+1, false);
			textures[i]->Bind(i+1);
			textureNames.push_back(identifier); 
		}
		LMX::Renderer::Submit(shader, m_vertexArray, offset);

		for (auto& i : textureNames)
		{
			LMX_PROFILE_SCOPE("Unbinding Textures");
			shader->SetUniform(i, 0, false);
		}
		shader->Unbind();
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

			for (auto& texture : textures)
			{
				texture->Init();
			}

			m_IsInit = true;
		}
	}
}