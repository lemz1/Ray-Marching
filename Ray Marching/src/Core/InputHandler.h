#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class InputHandler
{
public:
	InputHandler(GLFWwindow* window);
	~InputHandler();

	static const bool KeyIsPressed(int key);
	static const bool KeyIsHeld(int key);
	static const bool KeyIsReleased(int key);

	static const glm::vec2 GetMousePosition();
	static void CenterMousePosition();
	static void LockCursor();
	static void UnlockCursor();
	static const bool IsCursorLocked();
private:
	static InputHandler* s_Instance;

	// let me explain why these variables exist
	// because of how glfwGetKey works its going to act like
	// 1. you are holding the button down (there's basically no "has just been pressed")
	// 2. when you are not pressing the button its always calling release which is not what i want
	// basically i believe both of these things should be one time events, so thats why i added these variables
	// also the array size is a byte
	bool m_JustPressedKeyStates[256];
	bool m_JustReleasedKeyStates[256];

	GLFWwindow* m_Window;
};
