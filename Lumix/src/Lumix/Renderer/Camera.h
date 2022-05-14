#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Lumix/Core/Timestep.h"

namespace LMX
{
	class Camera
	{
	public:
		glm::vec3 Position = {0,0,0}, Front = {0,0,-1}, Up = {0,1,0};
		glm::mat4 ProjectionMatrix{1.f};

		Camera();
		virtual ~Camera();

		virtual glm::mat4 GetCameraMatrix() const;
		virtual glm::mat4 GetViewMatrix() const;
		virtual void DebugCameraController(float Speed, float rotSpeed, Timestep ts);
	};
}