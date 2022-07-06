#include "lmxpch.h"
#include "PerspectiveCamera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "Limux/Addon/ControllerInput.h"
#include "Limux/Core/MouseCodes.h"

namespace LMX
{
	PerspectiveCamera::PerspectiveCamera(float fov, float width, float height, float zNear, float zFar)
		:m_FOV(fov), m_Near(zNear), m_Far(zFar)
	{
		LMX_PROFILE_FUNCTION();
		Resize(width, height);
	}
	void PerspectiveCamera::Resize(float width, float height)
	{
		LMX_PROFILE_FUNCTION();
		m_Width = width;
		m_Height = height;
		SetProjectionMatrix(glm::perspective(m_FOV, m_Width / m_Height, m_Near, m_Far));
	}
	PerspectiveCamera::~PerspectiveCamera()
	{}
}