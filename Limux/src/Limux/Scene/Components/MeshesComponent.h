#pragma once
#include "Limux/Renderer/Vertex.h"
#include "Limux/Renderer/Mesh.h"
#include "Limux/Renderer/VertexArray.h"
#include "Limux/Scene/Scene.h"
namespace LMX
{
	
	struct MeshesComponent
	{
		std::vector<Ref<Mesh>> Meshes;
		MeshesComponent(Scene*) {};
		MeshesComponent() = default;
		MeshesComponent(const MeshesComponent&) = default;
		MeshesComponent(const std::vector<Ref<Mesh>>& meshes)
			: Meshes(meshes)
		{}

		void AddMesh(Ref<Mesh> mesh);
		void AddMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
		void InitAll();

		void RemoveMesh(size_t index);

		void PopBack();
		void Draw(Ref<Shader> shader, const glm::mat4& offset = glm::mat4(1.0f)) const;
	private:
		Ref<VertexArray> m_VertexArray;
	};
}
