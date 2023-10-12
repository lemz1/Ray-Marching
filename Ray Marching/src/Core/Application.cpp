#include "Application.h"

#include <iostream>

#include "Window.h"
#include <imgui/imgui_internal.h>

void InitializeOpenGL()
{
    glfwInit();

    // set opengl version to 4.6
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

    // use core profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

bool InitializeGlad()
{
    return gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

void InitializeImGui(GLFWwindow* window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable docking
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 460");
}

EventHandler* InitializeEventHandler(GLFWwindow* window)
{
    EventHandler* eventHandler = new EventHandler();

    glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height)
    {
        Event event;
        event.windowWidth = width;
        event.windowHeight = height;
        EventHandler::TriggerEventListeners(EventType::WindowResize, event);
    });

    /*glfwSetCursorPosCallback(window, [](GLFWwindow* window, double positionX, double positionY)
    {
        Event event;
        event.mousePositionX = positionX;
        event.mousePositionY = positionY;
        EventHandler::TriggerEventListeners(EventType::MouseMove, event);
    });

    glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
    {
        Event event;
        event.mouseButton = button;
        event.mouseAction = action;
        EventHandler::TriggerEventListeners(EventType::MouseButton, event);
    });*/

    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        Event event;
        event.key = key;
        event.keyAction = action;
        EventHandler::TriggerEventListeners(EventType::Keyboard, event);
    });

    return eventHandler;
}

InputHandler* InitializeKeyboardInputHandler(GLFWwindow* window)
{
    return new InputHandler(window);
}

FrameBuffer* InitializeViewportFrameBuffer()
{
    FrameBuffer* frameBuffer = new FrameBuffer();
    TextureSpecification spec;
    spec.width = Application::GetWidth();
    spec.height = Application::GetHeight();
    spec.format = TextureFormat::RGBA8;
    frameBuffer->AddTexture(spec);

    return frameBuffer;
}

void CreateDockSpace(ImGuiIO& io)
{
    // Create a full-screen ImGui window
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y));
    ImGui::Begin("FullScreenWindow", nullptr,
        ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar
        | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoNavFocus
        | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoFocusOnAppearing);

    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("DockSpace");
        
        // Set the default dock configuration if imgui.ini is not present
        if (!ImGui::DockBuilderGetNode(dockspace_id))
        {
            ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_DockSpace);
            ImGui::DockBuilderSetNodeSize(dockspace_id, io.DisplaySize);
            ImGui::DockBuilderDockWindow("Scene", dockspace_id);
            ImGui::DockBuilderFinish(dockspace_id);
        }

        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);
    }
    ImGui::End();
}

Application* Application::s_Instance = nullptr;

Application::Application(const char* title, uint32_t width, uint32_t height, Scene* initialScene)
{
    if (s_Instance)
    {
        std::cout << "Application already exists" << std::endl;
        return;
    }

    s_Instance = this;

    InitializeOpenGL();

    m_Window = Window::Create(title, width, height);
    if (!s_Instance->m_Window)
    {
        return;
    }

    if (!InitializeGlad())
    {
        std::cout << "Failed to initialize glad" << std::endl;
        return;
    }

    InitializeImGui(m_Window);

    m_EventHandler = InitializeEventHandler(m_Window);
    m_InputHandler = InitializeKeyboardInputHandler(m_Window);
    m_ViewportFrameBuffer = InitializeViewportFrameBuffer();

    AddScene(initialScene);
}

Application::~Application()
{
    delete m_EventHandler;
    delete m_InputHandler;
    delete m_ViewportFrameBuffer;

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

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

    ImGuiIO& io = ImGui::GetIO();

    while (!glfwWindowShouldClose(m_Window))
    {
        if (m_Scenes.size() == 0)
        {
            break;
        }

        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwPollEvents();

        double currentTime = glfwGetTime();
        double deltaTime = currentTime - m_LastUpdateTime;
        m_LastUpdateTime = currentTime;

        m_ViewportFrameBuffer->Bind();

        for (Scene* scene : m_Scenes)
        {
            scene->OnUpdate(deltaTime);
        }

        m_ViewportFrameBuffer->Unbind();

        // ImGui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        CreateDockSpace(io);

        // Display the ViewPortFrameBuffer
        ImGui::Begin("Scene", nullptr, ImGuiWindowFlags_NoCollapse);

        ImVec2 contentRegion = ImGui::GetContentRegionAvail();
        int imageWidth = contentRegion.x;
        int imageHeight = imageWidth / (16.f / 9.f);

        ImGui::Image(
            (void*)(intptr_t)m_ViewportFrameBuffer->GetTextureID(0),
            ImVec2(imageWidth, imageHeight),
            ImVec2(0, 1), 
            ImVec2(1, 0)
        );
        ImGui::End();

        for (Scene* scene : m_Scenes)
        {
            scene->OnImGuiUpdate(deltaTime);
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

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
