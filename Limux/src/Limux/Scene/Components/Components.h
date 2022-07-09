#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Limux/Renderer/Texture.h"
#include "Limux/Renderer/Mesh.h"
#include "Limux/Renderer/Shader.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include "Limux/Core/UUID.h"
#include "Limux/Scene/Entity.h"

#include "Camera/CameraComponent.h"

namespace LMX
{
	struct IDComponent
	{
		UUID ID;

		IDComponent() = default;
		IDComponent(const IDComponent&) = default;
		IDComponent(UUID id) : ID(id) {}
	};

	struct TransformComponent
	{
		glm::vec3 Translation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::mat4& transform);

		glm::mat4 GetTransform() const
		{

			return GetTranslationMatrix()
				* GetRotationMatrix()
				* GetScaleMatrix();
		}
		glm::mat4 GetTranslationMatrix() const;
		glm::mat4 GetRotationMatrix() const;
		glm::mat4 GetScaleMatrix() const;
		
		void LookAtEuler(const glm::vec3& dest, const glm::vec3& up = { 0.0f, 1.0f, 0.0f });
		static glm::vec3 LookAtEuler(const glm::vec3& dest, const glm::vec3& origin, const glm::vec3& up = { 0.0f, 1.0f, 0.0f });
	};

	struct TagComponent
	{
		std::string Tag;
		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag)
			: Tag(tag)
		{}
		operator std::string() const
		{
			return Tag;
		}
	};

	struct PathComponent
	{
		std::string Path;
		PathComponent() = default;
		PathComponent(const PathComponent&) = default;
		PathComponent(const std::string& path)
			: Path(path)
		{}
		operator std::string() const
		{
			return Path;
		}
	};

	struct TexturesComponent
	{
		std::vector<Ref<Texture>> Textures;
		TexturesComponent() = default;
		TexturesComponent(const TexturesComponent&) = default;
		TexturesComponent(const std::vector<Ref<Texture>>& textures)
			: Textures(textures)
		{}
		Ref<Texture2D> AddTexture2D(const std::string& path)
		{
			auto texture = Texture2D::Load(path);
			Textures.push_back(CastRef<Texture>(texture));
			return texture;
		}
		Ref<Texture> operator[](size_t index)
		{
			return Textures[index];
		}
	};

	struct MeshesComponent
	{
		std::vector<Ref<Mesh>> Meshes;
		MeshesComponent() = default;
		MeshesComponent(const MeshesComponent&) = default;
		MeshesComponent(const std::vector<Ref<Mesh>>& meshes)
			: Meshes(meshes)
		{}

		void AddMesh(Ref<Mesh> mesh)
		{
			Meshes.push_back(mesh);
		}

		void RemoveMesh(size_t index)
		{
			Meshes.erase(Meshes.begin() + index);
		}

		void PopBack()
		{
			Meshes.pop_back();
		}
		void Draw(Ref<Shader> shader, const glm::mat4& offset = glm::mat4(1.0f)) const;
	};
}

namespace LMX{
	struct NodeComponent
	{
		std::vector<Ref<Entity>> Children;
		NodeComponent() = default;
		NodeComponent(const NodeComponent& other):Children(other.Children){};
		NodeComponent(const std::vector<Ref<Entity>>& children)
			: Children(children)
		{}
		void AddChild(Ref<Entity> child);
		void RemoveChild(size_t index);
		void AddModel(const std::string& path, entt::registry& registry);

		virtual size_t size() const { return Children.size(); }
	};

	template<typename... Component>
	struct ComponentGroup
	{};

	using AllComponents =
		ComponentGroup<TransformComponent, IDComponent, TagComponent, 
		PathComponent, TexturesComponent, MeshesComponent, NodeComponent>;
}