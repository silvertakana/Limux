#include "lmxpch.h"
#include "Camera.h"

LMX::Camera::Camera(const glm::mat4& newProjMat)
{
	SetProjectionMatrix(newProjMat);
}

LMX::Camera::~Camera()
{}

void LMX::Camera::UpdateViewMatrix()
{
	m_ViewMatrix = glm::lookAt(Position, Position + Front, Up); UpdateViewProjectionMatrix();
}

void LMX::Camera::SetProjectionMatrix(const glm::mat4 & newProjMat)
{
	m_ProjectionMatrix = newProjMat; UpdateViewProjectionMatrix();
}

void LMX::Camera::UpdateViewProjectionMatrix()
{
	m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}
