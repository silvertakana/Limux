#include "lmxpch.h"
#include "PerspectiveController.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "Limux/Addon/ControllerInput.h"
#include "Limux/Core/MouseCodes.h"
#include <GLFW/glfw3.h>
#include "Limux/Core/Application.h"

namespace LMX
{
	void DebugPerspecCamUpdate(LMX::Ref<PerspectiveCamera> cam, float Speed, float rotSpeed, Timestep ts)
	{
		static bool s_Setup = false;
		if (!s_Setup)
		{

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
			s_Setup = true;
		}
		static bool firstClick;
		glm::vec3 newOrientation = cam->Front;
		
		float TurnSpeed = ts * rotSpeed;
		if (CtrlInp::IsPressed("TurnLeft"))
			newOrientation = glm::rotate(cam->Front, TurnSpeed, cam->Up);
		if (CtrlInp::IsPressed("TurnRight"))
			newOrientation = glm::rotate(cam->Front, -TurnSpeed, cam->Up);
		glm::vec3 Right = glm::normalize(glm::cross(cam->Front, cam->Up));
		if (CtrlInp::IsPressed("TurnUp"))
			newOrientation = glm::rotate(cam->Front, TurnSpeed, Right);
		if (CtrlInp::IsPressed("TurnDown"))
			newOrientation = glm::rotate(cam->Front, -TurnSpeed, Right);

		if (CtrlInp::IsPressed("Boost"))
			Speed *= 4;
		Speed *= ts;
		if (CtrlInp::IsPressed("Up"))
			cam->Position += cam->Front * Speed;
		if (CtrlInp::IsPressed("Down"))
			cam->Position += -cam->Front * Speed;
		if (CtrlInp::IsPressed("Left"))
			cam->Position += -Right * Speed;
		if (CtrlInp::IsPressed("Right"))
			cam->Position += Right * Speed;
		if (CtrlInp::IsPressed("FlyUp"))
			cam->Position += cam->Up * Speed;
		if (CtrlInp::IsPressed("FlyDown"))
			cam->Position += -cam->Up * Speed;

		// Handles mouse inputs
		if (Input::IsMouseButtonPressed(LMX_MOUSE_BUTTON_LEFT))
		{
			// Hides mouse cursor
			Input::SetInputMode(Input::InputType::CURSOR, Input::InputMode::CURSOR_HIDDEN);

			// Prevents camera from jumping on the first click
			if (firstClick)
			{
				Input::SetMousePosition((cam->Width / 2), (cam->Height / 2));
				firstClick = false;
			}

			// Stores the coordinates of the cursor
			// Fetches the coordinates of the cursor
			double mouseX = Input::GetMouseX();
			double mouseY = Input::GetMouseY();

			// Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
			// and then "transforms" them into degrees 
			float rotX = rotSpeed * ts * 3000.f * (float)(mouseY - (cam->Height / 2)) / cam->Height;
			float rotY = rotSpeed * ts * 3000.f * (float)(mouseX - (cam->Width / 2)) / cam->Width;

			// Calculates Upcoming vertical change in the cam->Front
			newOrientation = glm::rotate(cam->Front, glm::radians(-rotX), glm::normalize(glm::cross(cam->Front, cam->Up)));

			// Rotates the cam->Front left and right
			newOrientation = glm::rotate(newOrientation, glm::radians(-rotY), cam->Up);

			// Sets mouse cursor to the middle of the screen so that it doesn't end cam->Up roaming around
			Input::SetMousePosition((cam->Width / 2), (cam->Height / 2));
		}
		
		// Decides whether or not the next vertical cam->Front is legal or not
		if (abs(glm::angle(newOrientation, cam->Up) - glm::radians(90.0f)) <= glm::radians(80.0f))
		{
			cam->Front = newOrientation;
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