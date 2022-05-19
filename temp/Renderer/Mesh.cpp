#include "lmxpch.h"

#include "Mesh.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace LMX
{
	Mesh::Mesh(const std::vector<Vertex>& iVertices, const std::vector<GLuint>& iIndices, const std::vector<Texture>& iTextures)
		:vertices(iVertices), indices(iIndices), textures(iTextures)
	{
		VBO = { vertices, GL_STATIC_DRAW };
		EBO = { indices, GL_STATIC_DRAW };

		VAO.Attrib(0, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, pos));
		VAO.Attrib(1, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex, uv));
		VAO.Attrib(2, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, normal));
		VAO.Link(VBO, EBO, 0, sizeof(Vertex));
	}
	void Mesh::Draw(Shader& shader, glm::mat4 modelMatrix) const
	{
		shader.Use();
		glUniformMatrix4fv(shader.GetUni("uModelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
		std::map<Texture::Types, size_t> textureCounts;
		for (auto& i : shader.TextureUnits)
		{
			Texture::UnBind(i.second);
		}
		for (size_t i = 0; i < textures.size(); i++)
		{
			textureCounts[textures[i].type]++;
			std::string name = "";
			switch (textures[i].type)
			{
			case Texture::Types::diffuse:
				name += "diffuse";
				break;
			case Texture::Types::specular:
				name += "specular";
				break;
			case Texture::Types::normal:
				name += "normal";
				break;
			case Texture::Types::height:
				name += "height";
				break;
			default:
				name += "custom";
				break;
			}
			//shader.setInt(std::format("material.{0}_size", name), textureCounts[textures[i].type]);
			auto varName = std::format("material.textures_{0}[{1}]", name, textureCounts.at(textures[i].type) - 1);
			shader.Bindtexture(textures[i].ID, varName);
		}

		VAO.Bind();
		glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, 0);
		VAO.unBind();
		glActiveTexture(GL_TEXTURE0);

	}

}