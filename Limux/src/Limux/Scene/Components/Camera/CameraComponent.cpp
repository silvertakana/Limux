#include "lmxpch.h"
#include "CameraComponent.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include "Limux/Scene/Components/Components.h"

namespace LMX
{
	void CameraComponent::SetupPerspective(float fov, float width, float height, float zNear, float zFar)
	{
		FrameSize = { width , height };
		Projection = glm::perspective(fov, width / height, zNear, zFar);
	}
	void CameraComponent::SetupOrthographic(float width, float height, float zNear, float zFar)
	{
		FrameSize = { width , height };
		float halfWidth = width / 2.f;
		float halfHeight = height / 2.f;
		Projection = glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, zNear, zFar);
	}
	glm::mat4 CameraComponent::GenCamMatrix(glm::mat4 viewMatrix)
	{
		return Projection * viewMatrix;
	}
	glm::mat4 CameraComponent::GenCamMatrix(glm::vec3 Position, glm::vec3 Front, glm::vec3 Up)
	{
		return GenCamMatrix(GenViewMatrix(Position, Front, Up));
	}
	glm::mat4 CameraComponent::GenCamMatrix(const TransformComponent& transform, glm::vec3 Up)
	{
		return GenCamMatrix(GenViewMatrix(transform, Up));
	}
	glm::mat4 CameraComponent::GenViewMatrix(glm::vec3 Position, glm::vec3 Front, glm::vec3 Up)
	{
		return glm::lookAt(Position, Position + Front, Up);
	}
	glm::mat4 CameraComponent::GenViewMatrix(const TransformComponent& transform, glm::vec3 Up)
	{
		return GenViewMatrix(transform.Translation, glm::vec4(0, 0, 1, 1) * transform.GetRotationMatrix(),  Up);
	}
}