#include "lmxpch.h"
#include "SceneNode.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace LMX
{
	void SceneNode::Init()
	{
		LMX_PROFILE_FUNCTION();
		for (auto& mesh : Meshes)
		{
			mesh->Init();
		}
		for (auto& child : Children)
		{
			child->Init();
		}
	}
	void SceneNode::Draw(Ref<Shader> shader, const glm::mat4& offset) const
	{
		LMX_PROFILE_FUNCTION();
		for (auto& mesh : Meshes)
		{
			mesh->Draw(shader, offset * TransformMatrix);
		}
		for (auto& child : Children)
		{
			child->Draw(shader, offset * TransformMatrix);
		}
	}
	glm::mat4 SceneNode::UpdateTransform()
	{
		LMX_PROFILE_FUNCTION();
		TransformMatrix = glm::mat4 { 1.f };
		
		TransformMatrix = glm::translate(TransformMatrix, Translation);
		TransformMatrix *= glm::toMat4(glm::quat(Rotation));
		TransformMatrix = glm::scale(TransformMatrix, Scale);
		
		for (auto& child : Children)
		{
			child->UpdateTransform();
		}

		return TransformMatrix;
	}
	static std::string directory;
	void SceneNode::loadModel(const std::string& path)
	{
		LMX_PROFILE_FUNCTION();
		m_Path = path;
		Assimp::Importer importer;
		const aiScene* scene;
		{
			LMX_PROFILE_SCOPE("load model content");
			scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_OptimizeMeshes | aiProcess_RemoveRedundantMaterials | aiProcess_JoinIdenticalVertices);
		}
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			LMX_ERROR("Assimp failed to load model: {0}\nError: {1}",path,  importer.GetErrorString());
			return;
		}
		directory = path.substr(0, path.find_last_of('/'));

		processNode(scene->mRootNode, scene);
	}
	void SceneNode::processNode(aiNode * node, const aiScene * scene)
	{
		LMX_PROFILE_FUNCTION();
		m_Name = node->mName.C_Str();
		auto& transformation = node->mTransformation;
		{
			aiVector3D scal, rot, pos;
			transformation.Decompose(scal, rot, pos);
			Scale		= glm::vec3(scal.x, scal.y, scal.z);
			Rotation	= glm::vec3(rot .x, rot .y, rot .z);
			Translation	= glm::vec3(pos .x, pos .y, pos .z);
		}
		// process all the node's meshes (if any)
		auto AddMesh = [&](std::vector<Ref<Mesh>>* meshes, aiMesh* mesh, const aiScene* scene)
		{
			LMX_PROFILE_FUNCTION();
			meshes->push_back(processMesh(mesh, scene));
		};
		std::vector<std::future<void>> futures;
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			//futures.push_back(std::async(AddMesh, &Meshes, mesh, scene));
			Meshes.push_back(processMesh(mesh, scene));
		}
		// then do the same for each of its children
		auto AddChild = [](std::vector<Ref<SceneNode>>* children, aiNode* aiChild, const aiScene* scene)
		{
			LMX_PROFILE_FUNCTION();
			auto child = CreateRef<SceneNode>();
			children->push_back(child);
			child->processNode(aiChild, scene);
		};
		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			auto aiChild = node->mChildren[i];
			//futures.push_back(std::async(AddChild, &Children, aiChild, scene));
			auto child = CreateRef<SceneNode>();
			Children.push_back(child);
			child->processNode(aiChild, scene);
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
			Ref<Texture2D> texture = Texture2D::Create(directory + "/" + str.C_Str(), type);
			textures.push_back(texture);
		}
		return textures;
	}
	Ref<Mesh> SceneNode::processMesh(aiMesh * mesh, const aiScene * scene)
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
}