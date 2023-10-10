#include <glad/glad.h>

#include "../Core/Application.h"
#include "RayMarchingScene.h"

#include "../Debug/OpenGLDebug.h"

#define BindEvent(eventCallback) std::bind(&RayMarchingScene::eventCallback, this, std::placeholders::_1)

void RayMarchingScene::OnCreate()
{
	Debug::EnableGLDebugging();

	Application::GetEventHandler()->AddEventListener(new WindowResizeEventListener(BindEvent(OnWindowResize)));
	Application::GetEventHandler()->AddEventListener(new KeyboardEventListener(BindEvent(OnKeyboard)));

	m_FullscreenQuad = new FullscreenQuad();

	std::shared_ptr<Shader> shader = Shader::CreateVertexFragmentShader(
		"assets/shaders/default.vert",
		"assets/shaders/default.frag"
	);

	m_Quad = new Quad(shader);
}

void RayMarchingScene::OnUpdate(double deltaTime)
{
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
	Application::GetEventHandler()->ClearEventListeners();
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
	}
}
