#include "lmxpch.h"
#include "NodeComponent.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/pbrmaterial.h>

#include "Components.h"

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
		Children.erase(Children.begin() + index);
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
	std::tuple<
		std::vector<Vertex>,
		std::vector<uint32_t>,
		std::vector<Ref<Texture>>
	> processMesh(aiMesh* mesh, const aiScene* scene);

	void NodeComponent::AddModel(const std::string& path)
	{
		LMX_PROFILE_FUNCTION();

		AddChild(m_Scene->CreateEntity());

		auto entity = Entity(Children.back(), m_Scene);
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
		Entity.AddOrReplaceComponent<TexturesComponent>();

		// process all the node's meshes (if any)
		auto AddMeshai = [&](MeshesComponent* meshescom, TexturesComponent* texturescom, aiMesh* mesh, const aiScene* scene)
		{
			LMX_PROFILE_FUNCTION();
			auto [vertices, indices, textures] = processMesh(mesh, scene);
			meshescom->AddMesh(vertices, indices);
			texturescom->AddTextures(textures);
		};
		std::vector<std::future<void>> futures;
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			futures.push_back(std::async(AddMeshai, 
				&Entity.GetComponent<MeshesComponent>(),
				&Entity.GetComponent<TexturesComponent>(), mesh, scene));
		}
		Entity.GetComponent<MeshesComponent>().InitAll();

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
	std::tuple<
		std::vector<Vertex>,
		std::vector<uint32_t>,
		std::vector<Ref<Texture>>
	> processMesh(aiMesh* mesh, const aiScene* scene)
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
			std::vector<Ref<Texture2D>> textureMaps;
			
			textureMaps = loadMaterialTextures(material,
				aiTextureType_DIFFUSE, Texture2D::Diffuse);
			textures.insert(textures.end(), textureMaps.begin(), textureMaps.end());
			
			textureMaps = loadMaterialTextures(material,
				aiTextureType_SPECULAR, Texture2D::Specular);
			textures.insert(textures.end(), textureMaps.begin(), textureMaps.end());
			
			textureMaps = loadMaterialTextures(material,
				aiTextureType_SHININESS, Texture2D::Roughness);
			textures.insert(textures.end(), textureMaps.begin(), textureMaps.end());

			textureMaps = loadMaterialTextures(material,
				aiTextureType_AMBIENT, Texture2D::Ambient);
			textures.insert(textures.end(), textureMaps.begin(), textureMaps.end());
		}

		return std::make_tuple(vertices, indices, textures);
	}
}