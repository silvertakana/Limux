#include "lmxpch.h"
#include "OrthographicCamera.h"

#include "Limux/Addon/ControllerInput.h"
#include "Limux/Core/MouseButtonCodes.h"
namespace LMX
{
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float zNear, float zFar)
	{
		LMX_PROFILE_FUNCTION();
		SetProjectionMatrix(left, right, bottom, top, zNear, zFar);
	}

	OrthographicCamera::~OrthographicCamera()
	{}

	void OrthographicCamera::SetProjectionMatrix(float left, float right, float bottom, float top, float zNear, float zFar)
	{
		LMX_PROFILE_FUNCTION();
		Camera::SetProjectionMatrix(glm::ortho(left, right, bottom, top, zNear, zFar));
	}
}