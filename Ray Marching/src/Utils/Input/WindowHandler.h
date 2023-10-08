#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace WindowHandler
{
	void OnWindowResize(GLFWwindow* window, int width, int height);
	void Setup(GLFWwindow* window);
}