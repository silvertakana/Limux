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
	}
	PerspectiveCamera::~PerspectiveCamera()
	{}
}