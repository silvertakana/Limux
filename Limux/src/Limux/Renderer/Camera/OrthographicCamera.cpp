#include "lmxpch.h"
#include "OrthographicCamera.h"

#include "Limux/Addon/ControllerInput.h"
#include "Limux/Core/MouseButtonCodes.h"
namespace LMX
{
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float zNear, float zFar)
	{
		SetProjectionMatrix(left, right, bottom, top, zNear, zFar);
	}

	OrthographicCamera::~OrthographicCamera()
	{}

	void OrthographicCamera::SetProjectionMatrix(float left, float right, float bottom, float top, float zNear, float zFar)
	{
		Camera::SetProjectionMatrix(glm::ortho(left, right, bottom, top, zNear, zFar));
	}
}