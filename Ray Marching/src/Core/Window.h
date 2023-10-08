#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window
{
public:
	static GLFWwindow* CreateWindow();
private:
	static void InitializeOpenGL();
	static bool InitializeGlad();
};