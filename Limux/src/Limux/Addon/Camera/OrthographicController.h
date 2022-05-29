#pragma once
#include "Limux/Renderer/Camera/OrthographicCamera.h"
#include "Limux/Core/Core.h"
namespace LMX
{
	void DebugOrthoCamUpdate(LMX::Ref<OrthographicCamera> cam, float Speed, float rotSpeed, Timestep ts);
}
