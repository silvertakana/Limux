#include "lmxpch.h"
#include "MeshesComponent.h"
#include "Limux/Renderer/Renderer.h"

namespace LMX
{
	static std::mutex m_AddMeshMutex, m_RemoveMeshMutex;
	void MeshesComponent::AddMesh(Ref<Mesh> mesh)
	{
		std::lock_guard<std::mutex> lock(m_AddMeshMutex);
		Meshes.push_back(mesh);
	}
	void MeshesComponent::AddMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
	{
		AddMesh(CreateRef<Mesh>(vertices, indices));
	}
	void MeshesComponent::InitAll()
	{
		for (auto& mesh : Meshes)
			mesh->Init();
	}
	void MeshesComponent::RemoveMesh(size_t index)
	{
		std::lock_guard<std::mutex> lock(m_RemoveMeshMutex);
		Meshes.erase(Meshes.begin() + index);
	}
	void MeshesComponent::PopBack()
	{
		std::lock_guard<std::mutex> lock(m_RemoveMeshMutex);
		Meshes.pop_back();
	}
	void MeshesComponent::Draw(Ref<Shader> shader, const glm::mat4& offset) const
	{
		LMX_PROFILE_FUNCTION();
		for (auto& mesh : Meshes)
		{
			mesh->Draw(shader, offset);
		}
	}
}