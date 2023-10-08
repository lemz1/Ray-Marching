#include "MouseHandler.h"

void MouseHandler::OnMouseMove(GLFWwindow * window, double xpos, double ypos)
{
	if (inScene)
	{
		double deltaX = xpos - lastX;
		double deltaY = ypos - lastY;

		lastX = xpos;
		lastY = ypos;
	}
}

void MouseHandler::Setup(GLFWwindow* window)
{
	glfwSetCursorPosCallback(window, OnMouseMove);
}