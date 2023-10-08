#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Application.h"
#include "Window.h"

#include "../Utils/Input/WindowHandler.h"
#include "../Utils/Input/MouseHandler.h"
#include "../Utils/Input/KeyboardHandler.h"

Application Application::s_Instance;

void Application::Create(Scene* initialScene)
{
    s_Instance.m_Window = Window::CreateWindow();
    if (!s_Instance.m_Window)
    {
        return;
    }

    WindowHandler::Setup(s_Instance.m_Window);
    MouseHandler::Setup(s_Instance.m_Window);
    KeyboardHandler::Setup(s_Instance.m_Window);

    AddScene(initialScene);
}

void Application::Run()
{
    if (!s_Instance.m_Window)
    {
        return;
    }

    s_Instance.m_LastUpdateTime = glfwGetTime();

    while (!glfwWindowShouldClose(s_Instance.m_Window))
    {
        if (s_Instance.m_Scenes.size() == 0)
        {
            break;
        }

        double currentTime = glfwGetTime();
        double deltaTime = currentTime - s_Instance.m_LastUpdateTime;
        s_Instance.m_LastUpdateTime = currentTime;

        for (Scene* scene : s_Instance.m_Scenes)
        {
            scene->OnUpdate(deltaTime);
        }

        glfwPollEvents();

        glfwSwapBuffers(s_Instance.m_Window);
    }
}

void Application::Destroy()
{
    glfwDestroyWindow(s_Instance.m_Window);
    glfwTerminate();
}

void Application::AddScene(Scene* scene)
{
    auto iterator = std::find(s_Instance.m_Scenes.begin(), s_Instance.m_Scenes.end(), scene);
    if (iterator == s_Instance.m_Scenes.end())
    {
        // Scene is not in the vector, so add it
        scene->OnCreate();
        s_Instance.m_Scenes.push_back(scene);
    }
}


void Application::RemoveScene(Scene* scene)
{
    auto iterator = std::remove(s_Instance.m_Scenes.begin(), s_Instance.m_Scenes.end(), scene);
    s_Instance.m_Scenes.erase(iterator, s_Instance.m_Scenes.end());
    scene->OnDestroy();
}
