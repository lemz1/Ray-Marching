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

	m_ComputeShader = Shader::CreateComputeShader("assets/shaders/raymarch.comp");


	/*
	std::shared_ptr<Shader> computeShader = Shader::CreateComputeShader("assets/shaders/raymarch.comp");

	float data[] = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f }; // example data
	GLuint ssbo;
	glGenBuffers(1, &ssbo);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
	glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(data), data, GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ssbo);
	//glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0); // unbind

	computeShader->StartProgram();
	glDispatchCompute(5, 1, 1); // 5 items in the data array
	glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
	computeShader->StopProgram();

	float* gpuData = (float*)glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, sizeof(data), GL_MAP_READ_BIT);

	if (gpuData)
	{
		memcpy(data, gpuData, sizeof(data));
		glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
	}

	for (int i = 0; i < 5; i++)
	{
		std::cout << data[i] << std::endl;
	}

	glDeleteBuffers(1, &ssbo);
	*/
}

void RayMarchingScene::OnUpdate(double deltaTime)
{
	if (m_IsInScene)
	{
		m_CameraController.OnUpdate(deltaTime);
	}

	glClearColor(.1f, .1f, .1f, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	GLuint textureID = Application::GetViewportFrameBuffer()->GetTextureID(0);
	TextureSpecification spec = Application::GetViewportFrameBuffer()->GetTextureSpecification(0);

	glUseProgram(m_ComputeShader->GetID());
	glUniform1ui(glGetUniformLocation(m_ComputeShader->GetID(), "width"), spec.width);
	glUniform1ui(glGetUniformLocation(m_ComputeShader->GetID(), "height"), spec.height);
	glBindImageTexture(0, textureID, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA8);
	glDispatchCompute(
		ceil((float)spec.width / 16.f),
		ceil((float)spec.height / 16.f),
		1);
	glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
	glUseProgram(0);

	//m_Quad->Draw();
}

void RayMarchingScene::OnImGuiUpdate(double deltaTime)
{
	ImGui::Begin("Information");
	ImGui::Text("Last Render Time: %.5fms", deltaTime);
	ImGui::Text("FPS: %d", (int)(1 / deltaTime));
	ImGui::Text("\nCONTROLS");
	ImGui::Text("Exit Scene: ESCAPE or BACKSPACE");
	ImGui::Text("Enter Scene: SPACE or ENTER");
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
