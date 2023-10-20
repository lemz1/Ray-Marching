#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

#include "../Core/Application.h"

Camera::Camera(float verticalFOV, float nearClipPlane, float farClipPlane)
	: m_VerticalFOV(verticalFOV), m_NearClipPlane(nearClipPlane), m_FarClipPlane(farClipPlane)
{
	SetTransform(Transform());
	OnResize(Application::GetWidth(), Application::GetHeight());
}

Camera::Camera(const Transform & transform, float verticalFOV, float nearClipPlane, float farClipPlane)
	: m_VerticalFOV(verticalFOV), m_NearClipPlane(nearClipPlane), m_FarClipPlane(farClipPlane)
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
	m_ProjectionMatrix = glm::perspectiveFov(glm::radians(m_VerticalFOV), (float)m_Width, (float)m_Height, m_NearClipPlane, m_FarClipPlane);
	m_InverseProjectionMatrix = glm::inverse(m_ProjectionMatrix);

	m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

void Camera::RecalculateViewMatrix()
{
	m_ViewMatrix = glm::lookAt(m_Transform.position, m_Transform.position + m_Transform.rotation, glm::vec3(0, 1, 0));
	m_InverseViewMatrix = glm::inverse(m_ViewMatrix);

	m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

void Camera::RecalculateCameraToWorldMatrix()
{
	glm::mat4 translationMatrix = glm::mat4(
		1, 0, 0, m_Transform.position.x,
		0, 1, 0, m_Transform.position.y,
		0, 0, 1, m_Transform.position.z,
		0, 0, 0, 1
	);

	const float PI = 3.1415926f;
	float roll = m_Transform.rotation.x * PI / 180.f;
	float pitch = m_Transform.rotation.y * PI / 180.f;
	float yaw = m_Transform.rotation.z * PI / 180.f;

	glm::mat4 rotationMatrix = glm::mat4(
		cos(yaw) * cos(pitch),
		sin(yaw) * cos(pitch),
		-sin(pitch),
		0,

		cos(yaw) * sin(pitch) * cos(roll) - sin(yaw) * sin(roll),
		sin(yaw) * sin(pitch) * cos(roll) + cos(yaw) * sin(roll),
		cos(pitch) * sin(roll),
		0,

		cos(yaw) * sin(pitch) * sin(roll) + sin(yaw) * cos(roll),
		sin(yaw) * sin(pitch) * sin(roll) - cos(yaw) * cos(roll),
		cos(pitch) * cos(roll),
		0,

		0, 0, 0, 1
	);

	m_CameraToWorldMatrix = rotationMatrix * translationMatrix;
}
