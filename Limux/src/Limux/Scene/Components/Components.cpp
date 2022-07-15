#include "lmxpch.h"
#include "Limux/Scene/Entity.h"
#include "Components.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/gtx/matrix_decompose.hpp>

namespace LMX
{
	static std::mutex m_AddChildMutex, m_RemoveChildMutex;
	void NodeComponent::RemoveDestroyedChildren()
	{
		std::lock_guard<std::mutex> lock(m_RemoveChildMutex);
		Children.erase(std::remove_if(Children.begin(), Children.end(), [&](const entt::entity& entity)
			{
				return !m_Scene->GetReg().valid(entity);
			}), Children.end());
	}
	void NodeComponent::AddChild(entt::entity child)
	{
		std::lock_guard<std::mutex> lock(m_AddChildMutex);
		Children.push_back(child);
		auto& rootNodeCom = m_Scene->m_RootNode->GetComponent<NodeComponent>();
		rootNodeCom.RemoveChild(child);
	}
	void NodeComponent::RemoveChild(size_t index)
	{
		std::lock_guard<std::mutex> lock(m_RemoveChildMutex);
		Children.erase(Children.begin() + index );
	}

	void NodeComponent::RemoveChild(entt::entity child)
	{
		std::lock_guard<std::mutex> lock(m_RemoveChildMutex);
		auto& rootNodeCom = m_Scene->m_RootNode->GetComponent<NodeComponent>();
		auto& children = rootNodeCom.Children;
		Children.erase(std::remove(children.begin(), children.end(), child), children.end());
	}
	
	
	static std::string directory;
	
	void processNode(aiNode* node, const aiScene* scene, entt::entity entity, Scene* m_Scene);
	Ref<Mesh> processMesh(aiMesh* mesh, const aiScene* scene);
	
	void NodeComponent::AddModel(const std::string& path)
	{
		LMX_PROFILE_FUNCTION();
		
		AddChild(m_Scene->CreateEntity());
		
		auto entity = Entity(Children.back(), m_Scene);
		entity.AddComponent<PathComponent>(path);
		Assimp::Importer importer;
		const aiScene* scene;
		{
			LMX_PROFILE_SCOPE("load model content");
			scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_OptimizeMeshes | aiProcess_RemoveRedundantMaterials | aiProcess_JoinIdenticalVertices);
		}
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			LMX_ERROR("Assimp failed to load model: {0}\nError: {1}", path, importer.GetErrorString());
			return;
		}
		directory = path.substr(0, path.find_last_of('/'));

		processNode(scene->mRootNode, scene, entity, m_Scene);
	}
	void processNode(aiNode* node, const aiScene* scene, entt::entity entity, Scene* m_Scene)
	{
		LMX_PROFILE_FUNCTION();
		Entity Entity(entity, m_Scene);

		Entity.AddOrReplaceComponent<TagComponent>(node->mName.C_Str());
		
		auto& transformation = node->mTransformation;
		{
			auto& transform = Entity.AddOrReplaceComponent<TransformComponent>();
			
			*(aiMatrix4x4*)(&transform.Transform) = transformation;
		}
		
		Entity.AddOrReplaceComponent<MeshesComponent>();
		
		// process all the node's meshes (if any)
		auto AddMeshai = [&](MeshesComponent* meshescom, aiMesh* mesh, const aiScene* scene)
		{
			LMX_PROFILE_FUNCTION();
			meshescom->AddMesh(processMesh(mesh, scene));
		};
		std::vector<std::future<void>> futures;
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			futures.push_back(std::async(AddMeshai, &Entity.GetComponent<MeshesComponent>(), mesh, scene));
		}
		
		Entity.AddOrReplaceComponent<NodeComponent>();

		// then do the same for each of its children
		auto AddChildai = [&](NodeComponent* nodecom, aiNode* aiChild, const aiScene* scene)
		{
			LMX_PROFILE_FUNCTION();
			auto child = m_Scene->CreateEntity();
			processNode(aiChild, scene, child, m_Scene);
			nodecom->AddChild(child);
		};
		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			auto aiChild = node->mChildren[i];
			futures.push_back(std::async(AddChildai, &Entity.GetComponent<NodeComponent>(), aiChild, scene));
		}
		for (size_t i = 0; i < futures.size(); i++)
		{
			futures[i].wait();
		}
	}
	std::vector<Ref<Texture2D>> loadMaterialTextures(aiMaterial* mat, aiTextureType assimpType, Texture2D::TextureType type)
	{
		LMX_PROFILE_FUNCTION();
		std::vector<Ref<Texture2D>> textures;
		uint32_t count = mat->GetTextureCount(assimpType);
		for (unsigned int i = 0; i < count; i++)
		{
			LMX_PROFILE_SCOPE("load texture");
			aiString str;
			mat->GetTexture(assimpType, i, &str);
			Ref<Texture2D> texture = Texture2D::Load(directory + "/" + str.C_Str(), type);
			textures.push_back(texture);
		}
		return textures;
	}
	Ref<Mesh> processMesh(aiMesh* mesh, const aiScene* scene)
	{
		LMX_PROFILE_FUNCTION();
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
		std::vector<Ref<Texture>> textures;

		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			LMX_PROFILE_SCOPE("Load Vertices");
			Vertex vertex;
			auto& [Position, Normal, TexCoord, Color] = vertex; // extract vertex attributes
			// Process vertex positions, normals and texture coordinates
			// Positions
			Position.x = mesh->mVertices[i].x;
			Position.y = mesh->mVertices[i].y;
			Position.z = mesh->mVertices[i].z;

			// Normals
			Normal.x = mesh->mNormals[i].x;
			Normal.y = mesh->mNormals[i].y;
			Normal.z = mesh->mNormals[i].z;

			// Texture Coordinates
			if (mesh->mTextureCoords[0]) // Does the mesh contain texture coordinates?
			{
				TexCoord.x = mesh->mTextureCoords[0][i].x;
				TexCoord.y = mesh->mTextureCoords[0][i].y;
			}
			else
				TexCoord = glm::vec2(0.0f, 0.0f);

			// Vertex Color
			if (mesh->mColors[0])
			{
				Color.r = mesh->mColors[0][i].r;
				Color.g = mesh->mColors[0][i].g;
				Color.b = mesh->mColors[0][i].b;
				Color.a = mesh->mColors[0][i].a;
			}
			else
				Color = glm::vec4 { 0 };

			vertices.push_back(vertex);
		}
		// process indices
		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			LMX_PROFILE_SCOPE("Load Indices");
			aiFace face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}
		// process material
		if (mesh->mMaterialIndex >= 0)
		{
			LMX_PROFILE_SCOPE("Begin load textures");
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
			std::vector<Ref<Texture2D>> diffuseMaps = loadMaterialTextures(material,
				aiTextureType_DIFFUSE, Texture2D::Diffuse);
			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
			std::vector<Ref<Texture2D>> specularMaps = loadMaterialTextures(material,
				aiTextureType_SPECULAR, Texture2D::Specular);
			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		}

		return CreateRef<Mesh>(vertices, indices, textures);
	}
	TransformComponent::TransformComponent(Scene* scene, const glm::mat4& transform)
	{
		Transform = transform;
		//glm::quat rotationQuat;
		//glm::vec3 skew;
		//glm::vec4 perspective;
		//glm::decompose(transform, this->Scale, rotationQuat, this->Translation, skew, perspective);
		//this->Rotation = glm::eulerAngles(rotationQuat) * glm::pi<float>() / 180.f;
	}
	TransformComponent::TransformComposeMatrix TransformComponent::DecomposeTransformMatrix() const
	{
		return TransformComposeMatrix(
			GetTranslationMatrix(),
			GetRotationMatrix(),
			GetScaleMatrix()
			);
	}
	glm::mat4 TransformComponent::GetTranslationMatrix() const
	{
		return glm::translate(glm::mat4(1.0f), GetTranslation());
	}
	glm::mat4 TransformComponent::GetRotationMatrix() const
	{
		return glm::toMat4(GetRotation());
	}
	glm::mat4 TransformComponent::GetScaleMatrix() const
	{
		return glm::scale(glm::mat4(1.0f), GetScale());
	}
	TransformComponent::TransformCompose TransformComponent::DecomposeTransform() const
	{
		TransformCompose transform;
		glm::vec3 skew;
		glm::vec4 perspective;
		glm::decompose(Transform, transform.Scale, transform.RotationQuat, transform.Translation, skew, perspective);
		transform.RotationEuler = glm::eulerAngles(transform.RotationQuat);
		return transform;
	}
	glm::vec3 TransformComponent::GetTranslation() const
	{
		return DecomposeTransform().Translation;
	}
	glm::quat TransformComponent::GetRotation() const
	{
		return DecomposeTransform().RotationQuat;
	}
	glm::vec3 TransformComponent::GetScale() const
	{
		return DecomposeTransform().Scale;
	}
	void TransformComponent::SetTranslation(const glm::vec3& translation)
	{
		Transform = 
			glm::translate(glm::mat4(1.f), translation) *
			GetRotationMatrix() *
			GetScaleMatrix();
	}
	void TransformComponent::SetRotation(const glm::quat & rotation)
	{
		Transform =
			GetTranslationMatrix() *
			glm::toMat4(rotation) *
			GetScaleMatrix();
	}
	void TransformComponent::SetRotation(const glm::vec3& vector, float angle)
	{
		Transform =
			GetTranslationMatrix() *
			glm::rotate(glm::mat4{1.f}, angle, vector) *
			GetScaleMatrix();
	}
	void TransformComponent::SetRotation(const glm::vec3 & rotation)
	{
		SetRotation(glm::quat(rotation));
	}
	void TransformComponent::SetScale(const glm::vec3 & scale)
	{
		Transform =
			GetTranslationMatrix() *
			GetRotationMatrix() *
			glm::scale(glm::mat4(1.f), scale);
	}
	void TransformComponent::Translate(const glm::vec3& translation)
	{
		SetTranslation(GetTranslation() + translation);
	}
	void TransformComponent::Rotate(const glm::quat & rotation)
	{
		SetRotation(rotation * GetRotation());
	}
	void TransformComponent::Rotate(const glm::vec3 & rotation)
	{
		Rotate(glm::quat(rotation));
	}
	void TransformComponent::Rotate(const glm::vec3& vector, float angle)
	{
		Rotate(glm::rotate(glm::mat4(1.f), angle, vector));
	}
	void TransformComponent::Scale(const glm::vec3 & scale)
	{
		SetScale(GetScale() + scale);
	}
	static std::mutex m_AddMeshMutex, m_RemoveMeshMutex;
	void MeshesComponent::AddMesh(Ref<Mesh> mesh)
	{
		std::lock_guard<std::mutex> lock(m_AddMeshMutex);
		Meshes.push_back(mesh);
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