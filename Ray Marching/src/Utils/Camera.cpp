#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

#include "../Core/Application.h"

Camera::Camera(float verticalFOV, float nearPlane, float farPlane)
	: m_VerticalFOV(verticalFOV), m_NearPlane(nearPlane), m_FarPlane(farPlane)
{
	SetTransform(Transform());
	OnResize(Application::GetWidth(), Application::GetHeight());
}

Camera::Camera(const Transform & transform, float verticalFOV, float nearPlane, float farPlane)
	: m_VerticalFOV(verticalFOV), m_NearPlane(nearPlane), m_FarPlane(farPlane)
{
	SetTransform(transform);
	OnResize(Application::GetWidth(), Application::GetHeight());
}

void Camera::OnResize(uint32_t width, uint32_t height)
{
	if (m_Width == width && m_Height == height)
	{
		return;
	}

	m_Width = width;
	m_Height = height;

	RecalculateProjectionMatrix();
}

void Camera::RecalculateProjectionMatrix()
{
	m_ProjectionMatrix = glm::perspectiveFov(glm::radians(m_VerticalFOV), (float)m_Width, (float)m_Height, m_NearPlane, m_FarPlane);
	m_InverseProjectionMatrix = glm::inverse(m_ProjectionMatrix);

	m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

void Camera::RecalculateViewMatrix()
{
	m_ViewMatrix = glm::lookAt(m_Transform.position, m_Transform.position + m_Transform.rotation, glm::vec3(0, 1, 0));
	m_InverseViewMatrix = glm::inverse(m_ViewMatrix);

	m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}