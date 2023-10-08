#include "KeyboardHandler.h"

#include "MouseHandler.h"

void KeyboardHandler::OnKeyboardInput(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		if (key == GLFW_KEY_SPACE || key == GLFW_KEY_ENTER)
		{
			MouseHandler::inScene = true;
		}
		else if (key == GLFW_KEY_ESCAPE || key == GLFW_KEY_BACKSPACE)
		{
			MouseHandler::inScene = false;
		}
	}
}

void KeyboardHandler::Setup(GLFWwindow * window)
{
	glfwSetKeyCallback(window, OnKeyboardInput);
}
