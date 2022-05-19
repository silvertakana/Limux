#include "lmxpch.h"
#include "PerspectiveCamera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "Limux/Addon/ControllerInput.h"
#include "Limux/Core/MouseButtonCodes.h"

namespace LMX
{
	PerspectiveCamera::PerspectiveCamera(float fov, float width, float height, float zNear, float zFar)
		:Width(width), Height(height)
	{
		SetProjectionMatrix(glm::perspective(fov, Width / Height, zNear, zFar));
		
		CtrlInp::KeyMap["FlyUp"] = { {LMX_KEY_E} };
		CtrlInp::KeyMap["FlyDown"] = { {LMX_KEY_Q} };

		CtrlInp::KeyMap["Up"] = { {LMX_KEY_W} };
		CtrlInp::KeyMap["Down"] = { {LMX_KEY_S} };

		CtrlInp::KeyMap["Left"] = { {LMX_KEY_A} };
		CtrlInp::KeyMap["Right"] = { {LMX_KEY_D} };

		CtrlInp::KeyMap["TurnLeft"] = { {LMX_KEY_LEFT} };
		CtrlInp::KeyMap["TurnRight"] = { {LMX_KEY_RIGHT} };

		CtrlInp::KeyMap["TurnUp"] = { {LMX_KEY_UP} };
		CtrlInp::KeyMap["TurnDown"] = { {LMX_KEY_DOWN} };
	}
	PerspectiveCamera::~PerspectiveCamera()
	{}
	void PerspectiveCamera::DebugCameraUpdate(float Speed, float rotSpeed, Timestep ts)
	{
		static bool firstClick;
		
		float TurnSpeed = ts * rotSpeed;
		if (CtrlInp::IsPressed("TurnLeft"))
			Front = glm::rotate(Front, TurnSpeed, Up);
		if (CtrlInp::IsPressed("TurnRight"))
			Front = glm::rotate(Front, -TurnSpeed, Up);
		glm::vec3 Right = glm::normalize(glm::cross(Front, Up));
		if (CtrlInp::IsPressed("TurnUp"))
			Front = glm::rotate(Front, TurnSpeed, Right);
		if (CtrlInp::IsPressed("TurnDown"))
			Front = glm::rotate(Front, -TurnSpeed, Right);

		if (CtrlInp::IsPressed("Boost"))
			Speed *= 4;
		Speed *= ts;
		if (CtrlInp::IsPressed("Up"))
			Position += Front * Speed;
		if (CtrlInp::IsPressed("Down"))
			Position += -Front * Speed;
		if (CtrlInp::IsPressed("Left"))
			Position += -Right * Speed;
		if (CtrlInp::IsPressed("Right"))
			Position += Right * Speed;
		if (CtrlInp::IsPressed("FlyUp"))
			Position += Up * Speed;
		if (CtrlInp::IsPressed("FlyDown"))
			Position += -Up * Speed;

		// Handles mouse inputs
		if (Input::IsMouseButtonPressed(LMX_MOUSE_BUTTON_LEFT))
		{
			// Hides mouse cursor
			Input::SetInputMode(Input::InputType::CURSOR, Input::InputMode::CURSOR_HIDDEN);

			// Prevents camera from jumping on the first click
			if (firstClick)
			{
				Input::SetMousePosition((Width / 2), (Height / 2));
				firstClick = false;
			}

			// Stores the coordinates of the cursor
			// Fetches the coordinates of the cursor
			double mouseX = Input::GetMouseX();
			double mouseY = Input::GetMouseY();

			// Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
			// and then "transforms" them into degrees 
			float rotX = rotSpeed * ts * 3000.f * (float)(mouseY - (Height / 2)) / Height;
			float rotY = rotSpeed * ts * 3000.f * (float)(mouseX - (Width / 2)) / Width;

			// Calculates Upcoming vertical change in the Front
			glm::vec3 newOrientation = glm::rotate(Front, glm::radians(-rotX), glm::normalize(glm::cross(Front, Up)));

			// Decides whether or not the next vertical Front is legal or not
			if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
			{
				Front = newOrientation;
			}

			// Rotates the Front left and right
			Front = glm::rotate(Front, glm::radians(-rotY), Up);

			// Sets mouse cursor to the middle of the screen so that it doesn't end Up roaming around
			Input::SetMousePosition((Width / 2), (Height / 2));
		}
		else if (!Input::IsMouseButtonPressed(LMX_MOUSE_BUTTON_LEFT))
		{
			// Unhides cursor since camera is not looking around anymore
			Input::SetInputMode(Input::InputType::CURSOR, Input::InputMode::CURSOR_NORMAL);
			// Makes sure the next time the camera looks around it doesn't jump
			firstClick = true;
		}
	}
}