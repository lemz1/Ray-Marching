#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Window 
{
	GLFWwindow* Create(const char* title, uint32_t width, uint32_t height);
};
