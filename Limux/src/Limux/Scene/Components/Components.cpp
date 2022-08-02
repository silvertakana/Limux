#include "lmxpch.h"
#include "Limux/Scene/Entity.h"
#include "Components.h"

#include <glm/gtx/matrix_decompose.hpp>

namespace LMX
{

	TransformComponent::TransformComponent(Scene* scene, const glm::mat4& transform)
	{
		Transform = transform;
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
		return Transform[3];
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
	Ref<Texture2D> TexturesComponent::AddTexture2D(const std::string& path, Texture2D::TextureType type)
	{
		auto texture = Texture2D::Load(path, type);
		Textures.push_back(texture);
		return texture;
	}
	Ref<Texture2D> TexturesComponent::AddTexture2D(glm::vec4 color, Texture2D::TextureType type)
	{
		auto texture = Texture2D::Load(color);
		Textures.push_back(texture);
		return texture;
	}
	void TexturesComponent::UniformAll(Ref<Shader> shader)
	{
		LMX_PROFILE_FUNCTION();
		InitAll();
		shader->Bind();
		std::map<Texture2D::TextureType, uint32_t> count;
		Texture2D::TextureType type;
		std::string stringType, identifier;

		for (int i = 0; i < Textures.size(); i++)
		{
			LMX_PROFILE_SCOPE("Binding Textures");
			type = std::dynamic_pointer_cast<Texture2D>(Textures[i])->type;
			stringType = Texture2D::TextureTypeToString(type);
			stringType[0] = std::toupper(stringType[0]);
			identifier = std::format("u_Texture_{0}[{1}]", stringType, count[type]++);
			shader->SetUniform(identifier, i + 1, false);
			Textures[i]->Bind(i + 1);
		}
		shader->Unbind();

		
	}
	void TexturesComponent::UniformDefault(Ref<Shader> shader)
	{
		shader->Bind();
		
		std::map<Texture2D::TextureType, uint32_t> count;
		Texture2D::TextureType type;
		std::string stringType, identifier;
		
		for (int i = 0; i < Textures.size(); i++)
		{
			LMX_PROFILE_SCOPE("Unbinding Textures");
			type = std::dynamic_pointer_cast<Texture2D>(Textures[i])->type;
			stringType = Texture2D::TextureTypeToString(type);
			stringType[0] = std::toupper(stringType[0]);
			identifier = std::format("u_Texture_{0}{1}", stringType, count[type]++);
			shader->SetUniform(identifier, 0, false);
		}
		
		shader->Unbind();
	}
	void TexturesComponent::InitAll()
	{
		for (auto& texture : Textures)
		{
			texture->Init();
		}
	}
	
	void TexturesComponent::AddTextures(std::vector<Ref<Texture>> textures)
	{
		Textures.insert(Textures.end(), textures.begin(), textures.end());
	}
	
	void TexturesComponent::AddTextures(std::vector<Ref<Texture2D>> textures)
	{
		Textures.insert(Textures.end(), textures.begin(), textures.end());
	}
}