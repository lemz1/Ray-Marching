#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace MouseHandler
{
	void OnMouseMove(GLFWwindow* window, double xpos, double ypos);
	void Setup(GLFWwindow* window);

	static double lastX = 0;
	static double lastY = 0;
	static bool inScene = false;
}
