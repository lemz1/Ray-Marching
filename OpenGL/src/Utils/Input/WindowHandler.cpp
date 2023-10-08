#include "WindowHandler.h"

void WindowHandler::OnWindowResize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void WindowHandler::Setup(GLFWwindow* window)
{
	glfwSetFramebufferSizeCallback(window, OnWindowResize);
}
