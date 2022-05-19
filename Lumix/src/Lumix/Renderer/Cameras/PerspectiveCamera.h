#pragma once
#include "Camera.h"

namespace LMX
{
	class PerspectiveCamera : public Camera
	{
	public:
		PerspectiveCamera(float fov, float width, float height, float zNear = 0.01f, float zFar = 100.f);
		virtual ~PerspectiveCamera() override;
		virtual void DebugCameraUpdate(float Speed, float rotSpeed, Timestep ts);
		float Width, Height;
	};
}

