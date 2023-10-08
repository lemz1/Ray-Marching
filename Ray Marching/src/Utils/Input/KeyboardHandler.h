#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace KeyboardHandler
{
	void OnKeyboardInput(GLFWwindow* window, int key, int scancode, int action, int mods);
	void Setup(GLFWwindow* window);
}