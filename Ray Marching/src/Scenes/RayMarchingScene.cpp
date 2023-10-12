#include <glad/glad.h>

#include "../Core/Application.h"
#include "RayMarchingScene.h"

#include "../Debug/OpenGLDebug.h"

#include "../Core/InputHandler.h"

#define BindEvent(eventCallback) std::bind(&RayMarchingScene::eventCallback, this, std::placeholders::_1)

void RayMarchingScene::OnCreate()
{
	Debug::EnableGLDebugging();

	EventHandler::AddEventListener(new WindowResizeEventListener(BindEvent(OnWindowResize)));
	EventHandler::AddEventListener(new KeyboardEventListener(BindEvent(OnKeyboard)));

	std::shared_ptr<Shader> shader = Shader::CreateVertexFragmentShader(
		"assets/shaders/default.vert",
		"assets/shaders/default.frag"
	);

	std::shared_ptr<Camera> camera = std::make_shared<Camera>(Transform(glm::vec3(0, 0, 3), glm::vec3(0, 0, -1), glm::vec3(1)));

	m_CameraController = CameraController(camera);

	m_Quad = new Quad(shader, camera);
}

void RayMarchingScene::OnUpdate(double deltaTime)
{
	if (m_IsInScene)
	{
		m_CameraController.OnUpdate(deltaTime);
	}

	glClearColor(.1f, .1f, .1f, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	m_Quad->Draw();
}

void RayMarchingScene::OnImGuiUpdate(double deltaTime)
{
	ImGui::Begin("Render Information");
	ImGui::Text("Last Render Time: %.5fms", deltaTime);
	ImGui::End();
}

void RayMarchingScene::OnDestroy()
{
	delete m_Quad;
	EventHandler::ClearEventListeners();
}

void RayMarchingScene::OnWindowResize(const WindowResizeEvent& event)
{
	glViewport(0, 0, event.GetWidth(), event.GetHeight());
}

void RayMarchingScene::OnKeyboard(const KeyboardEvent& event)
{
	if (!event.IsPressed())
	{
		return;
	}

	if (event.GetKey() == GLFW_KEY_SPACE || event.GetKey() == GLFW_KEY_ENTER)
	{
		m_IsInScene = true;
	}
	else if (event.GetKey() == GLFW_KEY_ESCAPE || event.GetKey() == GLFW_KEY_BACKSPACE)
	{
		m_IsInScene = false;
		InputHandler::UnlockCursor();
	}
}
