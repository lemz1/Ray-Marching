#pragma once

#include <memory>

#include "Camera.h"


class CameraController
{
public:
	CameraController() = default;
	CameraController(std::shared_ptr<Camera>& camera)
		: m_Camera(camera), m_LastMousePosition(glm::vec2(0))
	{}

	void OnUpdate(double deltaTime);

	const float GetMouseSensitivity() const { return .0025f; }
	const float GetRotationSpeed() const { return .5f; }
	const float GetMovementSpeed() const { return 5.f; }

	const std::shared_ptr<Camera>& GetCamera() const { return m_Camera; }
private:
	void MoveCamera(double deltaTime);
private:
	std::shared_ptr<Camera> m_Camera;

	glm::vec2 m_LastMousePosition;
};