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

	m_FullscreenQuad = new FullscreenQuad();

	std::shared_ptr<Shader> shader = Shader::CreateVertexFragmentShader(
		"assets/shaders/default.vert",
		"assets/shaders/default.frag"
	);

	std::shared_ptr<Camera> camera = std::make_shared<Camera>(Transform(glm::vec3(0, 0, 2), glm::vec3(0, 0, -1), glm::vec3(1)));

	m_CameraController = CameraController(camera);

	m_Quad = new Quad(shader, camera);
}

void RayMarchingScene::OnUpdate(double deltaTime)
{
	if (m_IsInScene)
	{
		m_CameraController.OnUpdate(deltaTime);
	}

	m_FullscreenQuad->GetFrameBuffer()->Bind();

	glClearColor(.1f, .1f, .1f, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	m_Quad->Draw();

	m_FullscreenQuad->GetFrameBuffer()->Unbind();

	m_FullscreenQuad->Draw();
}

void RayMarchingScene::OnDestroy()
{
	delete m_Quad;
	delete m_FullscreenQuad;
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
