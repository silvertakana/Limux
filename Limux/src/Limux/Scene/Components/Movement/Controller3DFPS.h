#pragma once
#include "Limux/Scene/Components/Components.h"
#include "Limux/Core/Timestep.h"
#include "glm/glm.hpp"

namespace LMX
{
	void Controller3DFPSUpdate(TransformComponent& transform, float Speed, float rotSpeed, glm::vec3 front, glm::vec3 up, Timestep ts);
}