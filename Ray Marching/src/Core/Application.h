#pragma once

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

#include "Scene.h"
#include "EventHandler.h"
#include "InputHandler.h"

#include "FrameBuffer.h"

class Application
{
public:
	Application(const char* title, uint32_t width, uint32_t height, Scene* initialScene);
	~Application();
	void Run();

	static void AddScene(Scene* scene);
	static void RemoveScene(Scene* scene);

	static const Application* GetInstance() { return s_Instance; }

	static const uint32_t GetWidth();
	static const uint32_t GetHeight();
	static const GLFWwindow* GetWindow() { return s_Instance->m_Window; }

	static const FrameBuffer* GetViewportFrameBuffer() { return s_Instance->m_ViewportFrameBuffer; }
private:
	static Application* s_Instance;

	GLFWwindow* m_Window = nullptr;
	EventHandler* m_EventHandler = nullptr;
	InputHandler* m_InputHandler = nullptr;

	FrameBuffer* m_ViewportFrameBuffer = nullptr;

	double m_LastUpdateTime = 0;

	std::vector<Scene*> m_Scenes;
};
