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
#include "Limux/Scene/Scene.h"

#include "CameraComponent.h"
#include "ScriptableEntity.h"

namespace LMX
{
	struct IDComponent
	{
		UUID ID;

		IDComponent() = default;
		IDComponent(Scene*){};
		IDComponent(const IDComponent&) = default;
		IDComponent(Scene*, UUID id) : ID(id) {}
	};
	struct NativeScriptComponent
	{
		NativeScriptComponent(Scene*) {};
		ScriptableEntity* Instance = nullptr;

		ScriptableEntity* (*InstantiateScript)();
		void (*DestroyScript)(NativeScriptComponent*);

		template<typename T>
		void Bind()
		{
			InstantiateScript = []() { return static_cast<ScriptableEntity*>(new T()); };
			DestroyScript = [](NativeScriptComponent* nsc) { delete nsc->Instance; nsc->Instance = nullptr; };
		}
	};
	struct TransformComponent
	{
		glm::mat4 Transform{1.f};

		TransformComponent(Scene*) {};
		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(Scene*, const glm::mat4& transform);

		struct TransformComposeMatrix
		{
			glm::mat4 Translation;
			glm::mat4 Rotation;
			glm::mat4 Scale;
		};
		TransformComposeMatrix DecomposeTransformMatrix() const;
		glm::mat4 GetTranslationMatrix() const;
		glm::mat4 GetRotationMatrix() const;
		glm::mat4 GetScaleMatrix() const;

		struct TransformCompose
		{
			glm::vec3 Translation;
			glm::vec3 RotationEuler;
			glm::quat RotationQuat;
			glm::vec3 Scale;
		};
		TransformCompose DecomposeTransform() const;
		glm::vec3 GetTranslation() const;
		glm::quat GetRotation() const;
		glm::vec3 GetScale() const;
		
		void SetTranslation(const glm::vec3& translation);
		void SetRotation(const glm::quat& rotation);
		void SetRotation(const glm::vec3& vector, float angle);
		void SetRotation(const glm::vec3& rotation);
		void SetScale(const glm::vec3& scale);
		
		void Translate(const glm::vec3& translation);
		void Rotate(const glm::quat& rotation);
		void Rotate(const glm::vec3& rotation);
		void Rotate(const glm::vec3& vector, float angle);
		void Scale(const glm::vec3& scale);
	};

	struct TagComponent
	{
		std::string Tag;
		TagComponent(Scene*) {};
		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(Scene*, const std::string& tag)
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
		PathComponent(Scene*) {};
		PathComponent() = default;
		PathComponent(const PathComponent&) = default;
		PathComponent(Scene*, const std::string& path)
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
		TexturesComponent(Scene*) {};
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
		MeshesComponent(Scene*) {};
		MeshesComponent() = default;
		MeshesComponent(const MeshesComponent&) = default;
		MeshesComponent(const std::vector<Ref<Mesh>>& meshes)
			: Meshes(meshes)
		{}

		void AddMesh(Ref<Mesh> mesh);

		void RemoveMesh(size_t index);

		void PopBack();
		void Draw(Ref<Shader> shader, const glm::mat4& offset = glm::mat4(1.0f)) const;
	};
	
	struct NodeComponent
	{
		std::vector<entt::entity> Children;
		NodeComponent(Scene* scene):m_Scene(scene){};
		NodeComponent() = default;
		NodeComponent(const NodeComponent& other):Children(other.Children), m_Scene(other.m_Scene) {};
		NodeComponent(Scene* scene, const std::vector<entt::entity>& children)
			: Children(children), m_Scene(scene)
		{}
		void RemoveDestroyedChildren();
		void AddChild(entt::entity child);
		void RemoveChild(size_t index);
		void RemoveChild(entt::entity child);
		void AddModel(const std::string& path);

		virtual size_t size() const { return Children.size(); }
	protected:
		Scene* m_Scene = nullptr;
	};

	template<typename... Component>
	struct ComponentGroup
	{};

	using AllComponents =
		ComponentGroup<TransformComponent, IDComponent, TagComponent, 
		PathComponent, TexturesComponent, MeshesComponent, NodeComponent>;
}