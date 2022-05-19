#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Limux/Core/Timestep.h"

namespace LMX
{
	class Camera
	{
	protected:
		glm::mat4 m_ProjectionMatrix{1.f}, m_ViewMatrix{1.f}, m_ViewProjectionMatrix{1.f};
	public:
		glm::vec3 Position = {0,0,0}, Front = {0,0,-1}, Up = {0,1,0};

		Camera() = default;
		Camera(const glm::mat4& newProjMat);
		virtual ~Camera();

		virtual glm::mat4 GetViewProjMatrix() const { return m_ViewProjectionMatrix; };
		virtual glm::mat4 GetViewMatrix() const { return m_ViewMatrix; };
		virtual glm::mat4 GetProjectionMatrix() const { return m_ProjectionMatrix; };
		
		virtual void UpdateViewMatrix();
		virtual void SetProjectionMatrix(const glm::mat4& newProjMat);
	private:
		virtual void UpdateViewProjectionMatrix();
	};
}