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

	m_ComputeShader = Shader::CreateComputeShader("assets/shaders/raymarch.comp");
	
	m_Objects.push_back(SDFObject(Transform(glm::vec3(-3, 0, 3)), Material(), SDFObjectType::Sphere));
	m_Objects.push_back(SDFObject(Transform(glm::vec3(-2, -2, 3)), Material(glm::vec3(0.2f, 0, 0), glm::vec3(0.8f, 0, 0)), SDFObjectType::Box));
	m_Objects.push_back(SDFObject(Transform(glm::vec3(2, -3, 3), glm::vec3(0), glm::vec3(1, 0.25f, 1)), Material(), SDFObjectType::Torus));

	m_SDFObjectsBuffer = new StorageBuffer(m_Objects.data(), m_Objects.size() * sizeof(SDFObject), 1);
	m_PointLightsBuffer = new StorageBuffer(m_PointLights.data(), m_PointLights.size() * sizeof(PointLight), 2);
	m_DirectionalLightsBuffer = new StorageBuffer(m_DirectionalLights.data(), m_DirectionalLights.size() * sizeof(DirectionalLight), 3);
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

	glUniform1ui(glGetUniformLocation(m_ComputeShader->GetID(), "numSDFObjects"), m_Objects.size());
	glUniform1ui(glGetUniformLocation(m_ComputeShader->GetID(), "numPointLights"), m_PointLights.size());
	glUniform1ui(glGetUniformLocation(m_ComputeShader->GetID(), "numDirectionalLights"), m_DirectionalLights.size());

	m_SDFObjectsBuffer->SetData(m_Objects.data(), m_Objects.size() * sizeof(SDFObject));
	m_PointLightsBuffer->SetData(m_PointLights.data(), m_PointLights.size() * sizeof(PointLight));
	m_DirectionalLightsBuffer->SetData(m_DirectionalLights.data(), m_DirectionalLights.size() * sizeof(DirectionalLight));

	m_SDFObjectsBuffer->BindBufferBase();
	m_PointLightsBuffer->BindBufferBase();
	m_DirectionalLightsBuffer->BindBufferBase();

	glBindImageTexture(0, textureID, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA8);
	glDispatchCompute(
		ceil((float)spec.width / 16.f),
		ceil((float)spec.height / 16.f),
		1);
	glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

	m_SDFObjectsBuffer->UnbindBufferBase();
	m_PointLightsBuffer->UnbindBufferBase();
	m_DirectionalLightsBuffer->UnbindBufferBase();

	glUseProgram(0);
}

void RayMarchingScene::OnImGuiUpdate(double deltaTime)
{
	ImGui::Begin("Information");
	ImGui::Text("Last Render Time: %.5fms", deltaTime * 1000.f);
	ImGui::Text("FPS: %d", (int)(1 / deltaTime));
	ImGui::Text("\nCONTROLS");
	ImGui::Text("Exit Scene: ESCAPE or BACKSPACE");
	ImGui::Text("Enter Scene: SPACE or ENTER");
	ImGui::Text("Capped FPS Off/On: V");
	ImGui::End();
}

void RayMarchingScene::OnDestroy()
{
	EventHandler::ClearEventListeners();
}

void RayMarchingScene::OnWindowResize(const WindowResizeEvent& event)
{
	glViewport(0, 0, event.GetWidth(), event.GetHeight());
}

void RayMarchingScene::OnKeyboard(const KeyboardEvent& event)
{
	static bool s_Capped = true;
	if (!event.IsPressed())
	{
		return;
	}

	if (event.GetKey() == GLFW_KEY_V)
	{
		s_Capped = !s_Capped;
		glfwSwapInterval(s_Capped);
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
