#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window
{
public:
	static GLFWwindow* Create(const char* title, uint32_t width, uint32_t height);
private:
	static void InitializeOpenGL();
	static bool InitializeGlad();
};