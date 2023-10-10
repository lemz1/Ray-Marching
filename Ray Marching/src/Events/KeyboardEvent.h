#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct KeyboardEvent
{
public:
	KeyboardEvent(int key, int action) 
		: m_Key(key), m_Action(action)
	{}

	const int GetKey() const { return m_Key; }
	const bool IsPressed() const { return m_Action== GLFW_PRESS; }
	const bool IsHeld() const { return m_Action == GLFW_REPEAT; }
	const bool IsReleased() const { return m_Action == GLFW_RELEASE; }
private:
	int m_Key, m_Action;
};
