#pragma once

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../Scenes/Scene.h"

#include "../Events/EventHandler.h"

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

	static EventHandler* GetEventHandler() { return s_Instance->m_EventHandler; }
private:
	void InitializeEventHandler();
private:
	static Application* s_Instance;
	GLFWwindow* m_Window;
	EventHandler* m_EventHandler;

	double m_LastUpdateTime;

	std::vector<Scene*> m_Scenes;
};
