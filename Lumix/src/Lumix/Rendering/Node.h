#pragma once
#include "Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/gtc/quaternion.hpp>

class Node
{
public:
	Node(const std::string& path, bool flipUV = false)
	{
		LoadModel(path, flipUV);
	}
	Node(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, const std::vector<Texture>& textures)
	{
		AddMesh({ vertices, indices, textures });
	}
	Node() = default;
	std::string name;
	std::vector<Node> children;
	std::vector<Mesh> meshes;
	glm::mat4 transformMatrix{1.f};
	glm::vec3 rotation { 0.f };
	glm::vec3 position { 0.f }, scale {1.f};
	virtual glm::mat4& UpdateMatrix(glm::mat4 parentMatrix = glm::mat4{1.f});
	virtual void Draw(Shader& shader) const;
	Node& AddChild(const Node& child);
	Mesh& AddMesh(const Mesh& mesh);
private:
	void LoadModel(std::string path, bool flipUV = false);
	void ProcessNode(aiNode* node, const aiScene* scene, bool flipUV = false);
	static Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene, bool flipUV = false);
	static std::vector<Texture> loadMaterialTextures(aiMaterial* mat, Texture::Types type, bool flipUV = false);
};