#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Application
{
public:
	static void Run();

	static const Application& GetInstance() { return s_Instance; }

	const GLFWwindow* GetWindow() const { return m_Window; }
private:
	static Application s_Instance;
	GLFWwindow* m_Window;
};
