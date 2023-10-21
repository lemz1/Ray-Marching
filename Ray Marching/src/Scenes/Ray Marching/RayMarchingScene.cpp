#include "RayMarchingScene.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include <imgui/imgui_internal.h>

#include "../../Core/Application.h"
#include "../../Core/InputHandler.h"
#include "../../Debug/OpenGLDebug.h"
#include "../../Objects/ComputeRaymarchObject.h"

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

	std::shared_ptr<Camera> camera = std::make_shared<Camera>(Transform(glm::vec3(0, 1, 3), glm::vec3(0, 0, -1)));

	m_CameraController = CameraController(camera);

	std::shared_ptr<Shader> computeShader = Shader::CreateComputeShader("assets/shaders/raymarch.comp");
	
	std::vector<ComputeRaymarchObject> objects = std::vector<ComputeRaymarchObject>();
	objects.push_back(ComputeRaymarchObject(
		Transform(glm::vec3(2, 0, 5)),
		Material(glm::vec3(0.5f, 0, 0)),
		RaymarchObjectType::Box,
		1)
	);

	objects.push_back(ComputeRaymarchObject(
		Transform(glm::vec3(0, 0, 5), glm::vec3(0), glm::vec3(1, 0, 0)),
		Material(glm::vec3(0, 0.25f, 0.5f)),
		RaymarchObjectType::Sphere,
		1)
	);

	objects.push_back(ComputeRaymarchObject(
		Transform(glm::vec3(-2, 0, 5), glm::vec3(0), glm::vec3(4, 0.3f, 0)),
		Material(glm::vec3(0, 0.5f, 0)),
		RaymarchObjectType::Torus,
		1)
	);

	m_RayMarcher = RayMarcher::Create(computeShader, camera, objects);
}

void RayMarchingScene::OnUpdate(double deltaTime)
{
	if (m_IsInScene)
	{
		m_CameraController.OnUpdate(deltaTime);
	}

	glClearColor(.1f, .1f, .1f, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	
	m_RayMarcher->Render();
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
	ImGui::Text("Movement: W, A, S, D, E, Q");
	ImGui::End();

	ImGui::Begin("Objects");
	static int s_SelectedObjectIndex = -1;

	for (int i = 0; i < m_RayMarcher->GetObjects().size(); i++)
	{
		std::string objectName = "Object " + std::to_string(i);
		if (ImGui::Selectable(objectName.c_str()))
		{
			s_SelectedObjectIndex = i;
		}
	}
	ImGui::End();

	ImGui::Begin("Data");
	if (s_SelectedObjectIndex != -1)
	{
		ComputeRaymarchObject* object = &m_RayMarcher->GetObjects().at(s_SelectedObjectIndex);
		ImGui::DragFloat3("Position", glm::value_ptr(object->transform.position), 0.025f);
		ImGui::DragFloat3("Scale", glm::value_ptr(object->transform.scale), 0.01f, 0.01f, FLT_MAX);
		ImGui::DragFloat("Blend Strength", &object->blendStrength, 0.01f, 0.f, 1.f);
		ImGui::ColorPicker3("Color", glm::value_ptr(object->material.diffuseColor));
	}
	ImGui::End();
}


void RayMarchingScene::OnDestroy()
{
	EventHandler::ClearEventListeners();
	delete m_RayMarcher;
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
