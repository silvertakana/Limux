#pragma once
#include "Camera.h"
namespace LMX
{
	class OrthographicCamera : public Camera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top, float zNear, float zFar);
		virtual ~OrthographicCamera() override;
		
		virtual void SetProjectionMatrix(float left, float right, float bottom, float top, float zNear, float zFar);
		virtual void DebugCameraUpdate(float Speed, Timestep ts);
	};
}