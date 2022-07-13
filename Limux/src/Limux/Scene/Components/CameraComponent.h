#pragma once
#include "glm/glm.hpp"
namespace LMX
{
	struct TransformComponent;
	struct CameraComponent
	{
		glm::mat4 Projection{1.f};
		glm::vec2 FrameSize{0.f};

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
		CameraComponent(const glm::mat4& projection)
			: Projection(projection)
		{}
		void SetupPerspective(float fov, float width, float height, float zNear = 0.01f, float zFar = 100.f);
		void SetupOrthographic(float width, float height, float zNear = 0.01f, float zFar = 100.f);
		glm::mat4 GenCamMatrix(glm::mat4 viewMatrix) const;
		glm::mat4 GenCamMatrix(glm::vec3 Position, glm::vec3 Front, glm::vec3 Up) const;
		glm::mat4 GenCamMatrix(const TransformComponent& transform) const;
		glm::mat4 GenViewMatrix(glm::vec3 Position, glm::vec3 Front, glm::vec3 Up) const;
	};
}