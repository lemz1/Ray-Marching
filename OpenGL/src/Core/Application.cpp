#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Application.h"
#include "Window.h"

#include "../Utils/Input/WindowHandler.h"
#include "../Utils/Input/MouseHandler.h"
#include "../Utils/Input/KeyboardHandler.h"

Application Application::s_Instance;

void Application::Run()
{
	//s_Instance = Application();
	s_Instance.m_Window = Window::CreateWindow();
	if (!s_Instance.m_Window)
	{
		return;
	}

	WindowHandler::Setup(s_Instance.m_Window);
	MouseHandler::Setup(s_Instance.m_Window);
	KeyboardHandler::Setup(s_Instance.m_Window);

    while (!glfwWindowShouldClose(s_Instance.m_Window))
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(s_Instance.m_Window);

        glfwPollEvents();
    }

    glfwDestroyWindow(s_Instance.m_Window);
    glfwTerminate();
}
