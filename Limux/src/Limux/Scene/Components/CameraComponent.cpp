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
	glm::mat4 CameraComponent::GenCamMatrix(glm::mat4 viewMatrix) const
	{
		return Projection * glm::inverse(viewMatrix);
	}
	glm::mat4 CameraComponent::GenCamMatrix(glm::vec3 Position, glm::vec3 Front, glm::vec3 Up) const
	{
		return GenCamMatrix(GenViewMatrix(Position, Front, Up));
	}
	glm::mat4 CameraComponent::GenCamMatrix(const TransformComponent& transform) const
	{
		return GenCamMatrix(transform.Transform);
	}
	glm::mat4 CameraComponent::GenViewMatrix(glm::vec3 Position, glm::vec3 Front, glm::vec3 Up) const
	{
		return glm::lookAt(Position, Position + Front, Up);
	}
}