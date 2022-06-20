#include "lmxpch.h"
#include "Camera.h"

LMX::Camera::Camera(const glm::mat4& newProjMat)
{
	LMX_PROFILE_FUNCTION();
	SetProjectionMatrix(newProjMat);
}

LMX::Camera::~Camera()
{
	LMX_PROFILE_FUNCTION();
}

void LMX::Camera::UpdateViewMatrix()
{
	LMX_PROFILE_FUNCTION();
	m_ViewMatrix = glm::lookAt(Position, Position + Front, Up);
	UpdateViewProjectionMatrix();
}

void LMX::Camera::SetProjectionMatrix(const glm::mat4 & newProjMat)
{
	LMX_PROFILE_FUNCTION();
	m_ProjectionMatrix = newProjMat; UpdateViewProjectionMatrix();
}

void LMX::Camera::UpdateViewProjectionMatrix()
{
	LMX_PROFILE_FUNCTION();
	m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}
