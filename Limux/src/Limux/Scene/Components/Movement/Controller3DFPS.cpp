#include "lmxpch.h"

#include "Controller3DFPS.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "Limux/Addon/ControllerInput.h"
#include "Limux/Core/MouseCodes.h"

namespace LMX
{
	void Controller3DFPSUpdate(TransformComponent& transform, float Speed, float rotSpeed, glm::vec3 front, glm::vec3 up, Timestep ts)
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

		auto& [Translation, Rotation, Scale] = transform;
		
		glm::vec3 newOrientation = front;

		float TurnSpeed = ts * rotSpeed;
		if (CtrlInp::IsPressed("TurnLeft"))
			newOrientation = glm::rotate(front, TurnSpeed, up);
		if (CtrlInp::IsPressed("TurnRight"))
			newOrientation = glm::rotate(front, -TurnSpeed, up);
		glm::vec3 Right = glm::normalize(glm::cross(front, up));
		if (CtrlInp::IsPressed("TurnUp"))
			newOrientation = glm::rotate(front, TurnSpeed, Right);
		if (CtrlInp::IsPressed("TurnDown"))
			newOrientation = glm::rotate(front, -TurnSpeed, Right);

		if (CtrlInp::IsPressed("Boost"))
			Speed *= 4;
		Speed *= ts;
		//if (CtrlInp::IsPressed("Up"))
		//	cam->Position += front * Speed;
		//if (CtrlInp::IsPressed("Down"))
		//	cam->Position += -front * Speed;
		//if (CtrlInp::IsPressed("Left"))
		//	cam->Position += -Right * Speed;
		//if (CtrlInp::IsPressed("Right"))
		//	cam->Position += Right * Speed;
		//if (CtrlInp::IsPressed("FlyUp"))
		//	cam->Position += up * Speed;
		//if (CtrlInp::IsPressed("FlyDown"))
		//	cam->Position += -up * Speed;

		//if (abs(glm::angle(newOrientation, cam->Up) - glm::radians(90.0f)) <= glm::radians(80.0f))
		//{
		//	cam->Front = newOrientation;
		//}
	}
}
