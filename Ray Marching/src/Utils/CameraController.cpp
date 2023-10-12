#include "CameraController.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "../Core/InputHandler.h"

// thanks Cherno for some of the CameraController code (i took some of it from the Raytracing Series)

#define BindEvent(eventCallback) std::bind(&CameraController::eventCallback, this, std::placeholders::_1)

void CameraController::OnUpdate(double deltaTime)
{
	MoveCamera(deltaTime);
}

void CameraController::MoveCamera(double deltaTime)
{
	Transform transform = m_Camera->GetTransform();

	glm::vec3 upDirection = glm::vec3(0, 1, 0);
	glm::vec3 rightDirection = glm::cross(transform.rotation, upDirection);

	bool moved = false;

	if (InputHandler::KeyIsHeld(GLFW_KEY_W))
	{
		transform.position += transform.rotation * GetMovementSpeed() * (float)deltaTime;
		moved = true;
	} 
	else if (InputHandler::KeyIsHeld(GLFW_KEY_S))
	{
		transform.position -= transform.rotation * GetMovementSpeed() * (float)deltaTime;
		moved = true;
	}

	if (InputHandler::KeyIsHeld(GLFW_KEY_D))
	{
		transform.position += rightDirection * GetMovementSpeed() * (float)deltaTime;
		moved = true;
	}
	else if (InputHandler::KeyIsHeld(GLFW_KEY_A))
	{
		transform.position -= rightDirection * GetMovementSpeed() * (float)deltaTime;
		moved = true;
	}

	if (InputHandler::KeyIsHeld(GLFW_KEY_E))
	{
		transform.position += upDirection * GetMovementSpeed() * (float)deltaTime;
		moved = true;
	}
	else if (InputHandler::KeyIsHeld(GLFW_KEY_Q))
	{
		transform.position -= upDirection * GetMovementSpeed() * (float)deltaTime;
		moved = true;
	}

	if (!InputHandler::IsCursorLocked())
	{
		InputHandler::CenterMousePosition();
		InputHandler::LockCursor();
		m_LastMousePosition = InputHandler::GetMousePosition();
	}

	glm::vec2 mousePosition = InputHandler::GetMousePosition();
	glm::vec2 deltaPosition = (mousePosition - m_LastMousePosition) * GetMouseSensitivity();
	m_LastMousePosition = mousePosition;

	if (deltaPosition.x != 0.0f || deltaPosition.y != 0.0f)
	{
		float pitchDelta = deltaPosition.y * GetRotationSpeed();
		float yawDelta = deltaPosition.x * GetRotationSpeed();

		glm::quat quaternion = glm::normalize(glm::cross(glm::angleAxis(-pitchDelta, rightDirection), glm::angleAxis(-yawDelta, upDirection)));
		transform.rotation = glm::rotate(quaternion, transform.rotation);

		moved = true;
	}


	if (moved)
	{
		m_Camera->SetTransform(transform);
	}
}
