#pragma once
#include <glm/glm.hpp>
#include "Mesh.h"

struct aiNode;
struct aiMesh;
struct aiScene;

namespace LMX
{
	class SceneNode
	{
	public:
		glm::vec3 Translation { 0.f }, Rotation { 0.f }, Scale { 1.f }; // relative to parent
		glm::mat4 TransformMatrix{ 1.f };
		std::vector<Ref<Mesh>> Meshes;
		std::vector<Ref<SceneNode>> Children;
		SceneNode(const std::string& path)
		{
			loadModel(path);
		}
		void Init();
		SceneNode() = default;
		virtual void Draw(Ref<Shader> shader, const glm::mat4& offset = glm::mat4{1.f}) const;
		virtual glm::mat4 UpdateTransform();
	private:
		std::string m_Path, m_Name;
		void loadModel(const std::string& path);
		void processNode(aiNode* node, const aiScene* scene);
		Ref<Mesh> processMesh(aiMesh* mesh, const aiScene* scene);
	};
}