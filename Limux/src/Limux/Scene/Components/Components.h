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
#include "NodeComponent.h"
#include "ScriptableEntity.h"
#include "LightComponent.h"
#include "MeshesComponent.h"

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
		NativeScriptComponent() = default;
		NativeScriptComponent(Scene*) {};
		ScriptableEntity* Instance = nullptr;

		std::function<ScriptableEntity*			 ()> InstantiateScript	= nullptr;
		std::function<void (NativeScriptComponent*)> DestroyScript		= nullptr;

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
		TransformComponent& operator=(const TransformComponent& other) { Transform = other.Transform; return *this; }
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

	struct TexturesComponent
	{
		std::vector<Ref<Texture>> Textures;
		TexturesComponent(Scene*) {};
		TexturesComponent() = default;
		TexturesComponent(const TexturesComponent&) = default;
		TexturesComponent(const std::vector<Ref<Texture>>& textures)
			: Textures(textures)
		{}
		Ref<Texture2D> AddTexture2D(const std::string& path, Texture2D::TextureType type = Texture2D::TextureType::Auto);
		Ref<Texture2D> AddTexture2D(glm::vec4 color, Texture2D::TextureType type = Texture2D::TextureType::Auto);
		
		void AddTextures(std::vector<Ref<Texture>> textures);
		void AddTextures(std::vector<Ref<Texture2D>> textures);

		void UniformAll(Ref<Shader> shader);
		void UniformDefault(Ref<Shader> shader);
		void InitAll();
		
		Ref<Texture> operator[](size_t index)
		{
			return Textures[index];
		}
	};

	template<typename... Component>
	struct ComponentGroup
	{};

	using AllComponents =
		ComponentGroup<TransformComponent, IDComponent, TagComponent, 
		TexturesComponent, MeshesComponent, NodeComponent,
		NativeScriptComponent, CameraComponent, LightComponent>;
}