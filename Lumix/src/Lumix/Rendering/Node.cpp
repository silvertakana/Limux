#include "lmxpch.h"
#include "Node.h"
#include "Lumix/Log.h"
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <stb/stb_image.h>

namespace LMX
{
	glm::mat4 & Node::UpdateMatrix(glm::mat4 parentMatrix)
	{
		transformMatrix = parentMatrix;
		transformMatrix = glm::translate(transformMatrix, position);
		transformMatrix *= glm::eulerAngleXYZ(rotation.x, rotation.y, rotation.z);
		transformMatrix = glm::scale(transformMatrix, scale);
		for (auto& child : children)
		{
			child.UpdateMatrix(transformMatrix);
		}

		return transformMatrix;
	}

	void Node::Draw(Shader & shader) const
	{
		for (const auto& mesh : meshes)
		{
			mesh.Draw(shader, transformMatrix);
		}
		for (auto& child : children)
		{
			child.Draw(shader);
		}
	}

	Node & Node::AddChild(const Node & child)
	{
		children.push_back(child);
		return children.back();
	}

	Mesh & Node::AddMesh(const Mesh & mesh)
	{
		meshes.push_back(mesh);
		return meshes.back();
	}
	static std::string directory;
	void Node::LoadModel(std::string path, bool flipUV)
	{
		//TODO: Load model multithreaded
		static Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_OptimizeMeshes | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			ERROR("Unable to load model named: {0}\nError: {1}", path, importer.GetErrorString());
			return;
		}

		// retrieve the directory path of the filepath
		directory = path.substr(0, path.find_last_of('/'));

		ProcessNode(scene->mRootNode, scene, flipUV);
	}

	void Node::ProcessNode(aiNode* node, const aiScene* scene, bool flipUV)
	{

		name = node->mName.C_Str();
		// process all the node's meshes (if any)
		auto& transformation = node->mTransformation;
		{
			aiVector3D scal, rot, pos;
			transformation.Decompose(scal, rot, pos);
			scale = glm::vec3(scal.x, scal.y, scal.z);
			rotation = glm::vec3(rot.x, rot.y, rot.z);
			position = glm::vec3(pos.x, pos.y, pos.z);
		}
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			AddMesh(ProcessMesh(mesh, scene, flipUV));
		}
		// then do the same for each of its children
		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			//if (node->mNumMeshes > 0 or node->mChildren[i]->mNumChildren > 0)
			{
				children.emplace_back();
				children.back().ProcessNode(node->mChildren[i], scene, flipUV);
			}
		}
	}

	Mesh Node::ProcessMesh(aiMesh* ai_mesh, const aiScene* scene, bool flipUV)
	{
		Mesh mesh;

		for (unsigned int i = 0; i < ai_mesh->mNumVertices; i++)
		{
			// process vertex positions, normals and texture coordinates
			Vertex vertex;
			auto& [pos, uv, normal] = vertex;

			pos.x = ai_mesh->mVertices[i].x;
			pos.y = ai_mesh->mVertices[i].y;
			pos.z = ai_mesh->mVertices[i].z;

			normal.x = ai_mesh->mNormals[i].x;
			normal.y = ai_mesh->mNormals[i].y;
			normal.z = ai_mesh->mNormals[i].z;
			if (ai_mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
			{
				uv.x = ai_mesh->mTextureCoords[0][i].x;
				uv.y = ai_mesh->mTextureCoords[0][i].y;
			}
			else
				uv = glm::vec2(0.0f, 0.0f);

			mesh.vertices.push_back(vertex);
		}
		// process indices
		for (unsigned int i = 0; i < ai_mesh->mNumFaces; i++)
		{
			aiFace face = ai_mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
				mesh.indices.push_back(face.mIndices[j]);
		}
		// process material
		if (ai_mesh->mMaterialIndex >= 0)
		{
			aiMaterial* material = scene->mMaterials[ai_mesh->mMaterialIndex];
			std::vector<Texture> diffuseMaps = loadMaterialTextures(material,
				Texture::Types::diffuse, flipUV);
			mesh.textures.insert(mesh.textures.end(), diffuseMaps.begin(), diffuseMaps.end());
			std::vector<Texture> specularMaps = loadMaterialTextures(material,
				Texture::Types::specular, flipUV);
			mesh.textures.insert(mesh.textures.end(), specularMaps.begin(), specularMaps.end());
		}

		return Mesh(mesh.vertices, mesh.indices, mesh.textures);
	}

	std::vector<Texture> Node::loadMaterialTextures(aiMaterial* mat, Texture::Types type, bool flipUV)
	{
		static std::map<std::string, Texture> loaded_textures;
		aiTextureType aiType;
		switch (type)
		{
		case Texture::Types::diffuse:
			aiType = aiTextureType_DIFFUSE;
			break;
		case Texture::Types::specular:
			aiType = aiTextureType_SPECULAR;
			break;
		case Texture::Types::normal:
			aiType = aiTextureType_NORMALS;
			break;
		case Texture::Types::height:
			aiType = aiTextureType_HEIGHT;
			break;
		default:
			aiType = aiTextureType_NONE;
			break;
		}
		std::vector<Texture> textures;
		for (unsigned int i = 0; i < mat->GetTextureCount(aiType); i++)
		{
			aiString str;
			mat->GetTexture(aiType, i, &str);
			std::string path = directory + "/" + str.C_Str();
			textures.emplace_back(path, type, flipUV);
		}
		return textures;
	}

}