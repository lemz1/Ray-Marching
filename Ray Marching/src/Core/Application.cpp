#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Application.h"
#include "Window.h"

Application* Application::s_Instance = nullptr;

Application::Application(const char* title, uint32_t width, uint32_t height, Scene* initialScene)
{
    if (s_Instance)
    {
        std::cout << "Application already exists" << std::endl;
        return;
    }

    s_Instance = this;

    m_Window = Window::Create(title, width, height);
    if (!s_Instance->m_Window)
    {
        return;
    }

    InitializeEventHandler();

    AddScene(initialScene);
}

Application::~Application()
{
    glfwDestroyWindow(m_Window);
    glfwTerminate();

    for (Scene* scene : m_Scenes)
    {
        delete scene;
    }

    s_Instance = nullptr;
}

void Application::Run()
{
    if (!m_Window)
    {
        return;
    }

    m_LastUpdateTime = glfwGetTime();

    while (!glfwWindowShouldClose(m_Window))
    {
        if (m_Scenes.size() == 0)
        {
            break;
        }

        double currentTime = glfwGetTime();
        double deltaTime = currentTime - m_LastUpdateTime;
        m_LastUpdateTime = currentTime;

        for (Scene* scene : m_Scenes)
        {
            scene->OnUpdate(deltaTime);
        }

        glfwPollEvents();

        glfwSwapBuffers(m_Window);
    }
}

void Application::AddScene(Scene* scene)
{
    auto iterator = std::find(s_Instance->m_Scenes.begin(), s_Instance->m_Scenes.end(), scene);
    if (iterator == s_Instance->m_Scenes.end())
    {
        // Scene is not in the vector, so add it
        scene->OnCreate();
        s_Instance->m_Scenes.push_back(scene);
    }
}


void Application::RemoveScene(Scene* scene)
{
    auto iterator = std::remove(s_Instance->m_Scenes.begin(), s_Instance->m_Scenes.end(), scene);
    s_Instance->m_Scenes.erase(iterator, s_Instance->m_Scenes.end());
    scene->OnDestroy();
}

const uint32_t Application::GetWidth()
{
    int width;
    glfwGetWindowSize(s_Instance->m_Window, &width, nullptr);
    return width;
}

const uint32_t Application::GetHeight()
{
    int height;
    glfwGetWindowSize(s_Instance->m_Window, nullptr, &height);
    return height;
}

void Application::InitializeEventHandler()
{
    m_EventHandler = new EventHandler();

    glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
    {
        Event event;
        event.windowWidth = width;
        event.windowHeight = height;
        Application::GetEventHandler()->TriggerEventListeners(EventType::WindowResize, event);
    });

    glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double positionX, double positionY)
    {
        Event event;
        event.mousePositionX = positionX;
        event.mousePositionY = positionY;
        Application::GetEventHandler()->TriggerEventListeners(EventType::MouseMove, event);
    });

    glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
    {
        Event event;
        event.mouseButton = button;
        event.mouseAction = action;
        Application::GetEventHandler()->TriggerEventListeners(EventType::MouseButton, event);
    });

    glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        Event event;
        event.key = key;
        event.keyAction = action;
        Application::GetEventHandler()->TriggerEventListeners(EventType::Keyboard, event);
    });
}
