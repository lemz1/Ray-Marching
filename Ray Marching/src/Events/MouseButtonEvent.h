#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct MouseButtonEvent
{
public:
	MouseButtonEvent(int button, int action) 
		: m_Button(button), m_Action(action)
	{}

	const int GetButton() const { return m_Button; }
	const bool IsPressed() const { return m_Action == GLFW_PRESS; }
	const bool IsHeld() const { return m_Action == GLFW_REPEAT; }
	const bool IsReleased() const { return m_Action == GLFW_RELEASE; }
private:
	int m_Button, m_Action;
};
