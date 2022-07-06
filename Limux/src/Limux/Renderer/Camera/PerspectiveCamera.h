#pragma once
#include "Camera.h"

namespace LMX
{
	class PerspectiveCamera : public Camera
	{
		float m_Width, m_Height;
		float m_FOV;
		float m_Near, m_Far;
	public:
		PerspectiveCamera(float fov, float width, float height, float zNear = 0.01f, float zFar = 100.f);
		virtual void Resize(float width, float height);
		virtual glm::vec2 GetSize() { return { m_Width, m_Height }; }
		virtual float GetWidth() { return m_Width; }
		virtual float GetHeight() { return m_Height; }
		virtual float Ratio() { return m_Width / m_Height; }
		virtual ~PerspectiveCamera() override;
	};
}

