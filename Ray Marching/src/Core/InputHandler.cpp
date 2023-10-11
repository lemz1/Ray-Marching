#include "InputHandler.h"

#include <iostream>

InputHandler* InputHandler::s_Instance = nullptr;

InputHandler::InputHandler(GLFWwindow* window)
{
	if (s_Instance)
	{
		std::cout << "InputHandler already exists" << std::endl;
		return;
	}

	for (int i = 0; i < 256; i++)
	{
		m_JustPressedKeyStates[i] = false;
		m_JustReleasedKeyStates[i] = true;
	}

	s_Instance = this;

	m_Window = window;
}

InputHandler::~InputHandler()
{
	s_Instance = nullptr;
}

const bool InputHandler::KeyIsPressed(int key)
{
	// im not using a bang for the key state check for clarity
	bool isPressed = glfwGetKey(s_Instance->m_Window, key) == GLFW_PRESS && s_Instance->m_JustPressedKeyStates[key] == false;

	if (isPressed)
	{
		s_Instance->m_JustPressedKeyStates[key] = true;
		s_Instance->m_JustReleasedKeyStates[key] = false;
	}

	return isPressed;
}

const bool InputHandler::KeyIsHeld(int key)
{
	return glfwGetKey(s_Instance->m_Window, key) == GLFW_PRESS;
}

const bool InputHandler::KeyIsReleased(int key)
{
	// im not using a bang for the key state check for clarity
	bool isReleased = glfwGetKey(s_Instance->m_Window, key) == GLFW_RELEASE && s_Instance->m_JustReleasedKeyStates[key] == false;

	if (isReleased)
	{
		s_Instance->m_JustPressedKeyStates[key] = false;
		s_Instance->m_JustReleasedKeyStates[key] = true;
	}

	return isReleased;
}

const glm::vec2& InputHandler::GetMousePosition()
{
	double positionX, positionY;
	glfwGetCursorPos(s_Instance->m_Window, &positionX, &positionY);
	return glm::vec2(positionX, positionY);
}

void InputHandler::CenterMousePosition()
{
	int width, height;
	glfwGetWindowSize(s_Instance->m_Window, &width, &height);
	glfwSetCursorPos(s_Instance->m_Window, width / 2, height / 2);
}

void InputHandler::LockCursor()
{
	glfwSetInputMode(s_Instance->m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void InputHandler::UnlockCursor()
{
	glfwSetInputMode(s_Instance->m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

const bool InputHandler::IsCursorLocked()
{
	return glfwGetInputMode(s_Instance->m_Window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED;
}
