#include "lmxpch.h"
#include "OrthographicController.h"

#include "Limux/Addon/ControllerInput.h"


namespace LMX
{
	void DebugOrthoCamUpdate(LMX::Ref<OrthographicCamera> cam, float Speed, float rotSpeed, Timestep ts)
	{
		LMX_PROFILE_FUNCTION();
		CtrlInp::KeyMap["cam->Up"] = { {LMX_KEY_W} };
		CtrlInp::KeyMap["Down"] = { {LMX_KEY_S} };

		CtrlInp::KeyMap["Left"] = { {LMX_KEY_A} };
		CtrlInp::KeyMap["Right"] = { {LMX_KEY_D} };
		
		glm::vec3 Right = glm::normalize(glm::cross(cam->Front, cam->Up));
		if (CtrlInp::IsPressed("Boost"))
			Speed *= 4;
		Speed *= ts;
		if (CtrlInp::IsPressed("Up"))
			cam->Position += cam->Up * Speed;
		if (CtrlInp::IsPressed("Down"))
			cam->Position += -cam->Up * Speed;
		if (CtrlInp::IsPressed("Left"))
			cam->Position += -Right * Speed;
		if (CtrlInp::IsPressed("Right"))
			cam->Position += Right * Speed;
	}
}
