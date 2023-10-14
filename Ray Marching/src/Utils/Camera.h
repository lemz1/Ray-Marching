#pragma once

#include <glm/glm.hpp>

#include "Transform.h"

class Camera
{
public:
	Camera(float verticalFOV = 45.f, float nearClipPlane = .1f, float farClipPlane = 1000.f);
	Camera(const Transform& transform, float verticalFOV = 45.f, float nearClipPlane = .1f, float farClipPlane = 1000.f);

	void OnResize(uint32_t width, uint32_t height);

	const Transform& GetTransform() const { return m_Transform; }
	void SetTransform(const Transform& transform) { m_Transform = transform; RecalculateViewMatrix(); }

	const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
	const glm::mat4& GetInverseViewMatrix() const { return m_InverseViewMatrix; }

	const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
	const glm::mat4& GetInverseProjectionMatrix() const { return m_InverseProjectionMatrix; }

	const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

	const float GetVerticalFOV() { return m_VerticalFOV; }
	const float GetNearClipPlane() { return m_NearClipPlane; }
	const float GetFarClipPlane() { return m_FarClipPlane; }
	const uint32_t GetWidth() { return m_Width; }
	const uint32_t GetHeight() { return m_Height; }
private:
	void RecalculateProjectionMatrix();
	void RecalculateViewMatrix();
private:
	Transform m_Transform;

	glm::mat4 m_ViewMatrix = glm::mat4(1);
	glm::mat4 m_InverseViewMatrix = glm::mat4(1);

	glm::mat4 m_ProjectionMatrix = glm::mat4(1);
	glm::mat4 m_InverseProjectionMatrix = glm::mat4(1);

	glm::mat4 m_ViewProjectionMatrix = glm::mat4(1);

	float m_VerticalFOV, m_NearClipPlane, m_FarClipPlane;

	uint32_t m_Width, m_Height;
};