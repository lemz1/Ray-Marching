#pragma once

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Scene.h"

class Application
{
public:
	static void Create(Scene* initialScene);
	static void Run();
	static void Destroy();

	static void AddScene(Scene* scene);
	static void RemoveScene(Scene* scene);

	static const Application& GetInstance() { return s_Instance; }

	static const uint32_t GetWidth();
	static const uint32_t GetHeight();
	const GLFWwindow* GetWindow() const { return m_Window; }
private:
	static Application s_Instance;
	GLFWwindow* m_Window;

	double m_LastUpdateTime;

	std::vector<Scene*> m_Scenes;
};
