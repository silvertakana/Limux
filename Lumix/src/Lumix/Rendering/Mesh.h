#pragma once
#include <glm/glm.hpp>
#include <glad/glad.h>
#include "Shader.h"
#include "Buffer.h"
#include "VAO.h"
#include "Vertex.h"
#include "Texture.h"
class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;
	VertArrObj VAO;
	Buffer VBO;
	Buffer EBO;

	Mesh(const std::vector<Vertex>& iVertices, const std::vector<GLuint>& iIndices, const std::vector<Texture>& iTextures);
	Mesh() = default;
	virtual void Draw(Shader& shader, glm::mat4 modelMatrix) const;
};

