#include "lmxpch.h"
#include "OrthographicCamera.h"

#include "Limux/Addon/ControllerInput.h"
#include "Limux/Core/MouseButtonCodes.h"
namespace LMX
{
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float zNear, float zFar)
	{
		SetProjectionMatrix(left, right, bottom, top, zNear, zFar);

		CtrlInp::KeyMap["Up"] = { {LMX_KEY_W} };
		CtrlInp::KeyMap["Down"] = { {LMX_KEY_S} };

		CtrlInp::KeyMap["Left"] = { {LMX_KEY_A} };
		CtrlInp::KeyMap["Right"] = { {LMX_KEY_D} };
	}

	OrthographicCamera::~OrthographicCamera()
	{}

	void OrthographicCamera::SetProjectionMatrix(float left, float right, float bottom, float top, float zNear, float zFar)
	{
		Camera::SetProjectionMatrix(glm::ortho(left, right, bottom, top, zNear, zFar));
	}

	void OrthographicCamera::DebugCameraUpdate(float Speed, Timestep ts)
	{
		glm::vec3 Right = glm::normalize(glm::cross(Front, Up));
		if (CtrlInp::IsPressed("Boost"))
			Speed *= 4;
		Speed *= ts;
		if (CtrlInp::IsPressed("Up"))
			Position += Up * Speed;
		if (CtrlInp::IsPressed("Down"))
			Position += -Up * Speed;
		if (CtrlInp::IsPressed("Left"))
			Position += -Right * Speed;
		if (CtrlInp::IsPressed("Right"))
			Position += Right * Speed;
	}
}