#pragma once
#include "Limux/Renderer/Camera/PerspectiveCamera.h"
#include "Limux/Core/Base.h"
namespace LMX
{
	void DebugPerspecCamUpdate(LMX::Ref<PerspectiveCamera> cam, float Speed, float rotSpeed, Timestep ts);
}
