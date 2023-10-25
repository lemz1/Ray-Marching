#include "RayMarchingScene.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include <imgui/imgui_internal.h>

#include "../../Core/Application.h"
#include "../../Core/InputHandler.h"
#include "../../Debug/OpenGLDebug.h"
#include "../../Objects/ComputeRaymarchObject.h"
#include "GLFW/glfw3native.h"

#define BindEvent(eventCallback) std::bind(&RayMarchingScene::eventCallback, this, std::placeholders::_1)

void RayMarchingScene::OnCreate()
{
	Debug::EnableGLDebugging();

	EventHandler::AddEventListener(new WindowResizeEventListener(BindEvent(OnWindowResize)));
	EventHandler::AddEventListener(new KeyboardEventListener(BindEvent(OnKeyboard)));

	std::shared_ptr<Camera> camera = std::make_shared<Camera>(Transform(glm::vec3(0, 1, 3), glm::vec3(0, 0, -1)));

	m_CameraController = CameraController(camera);

	const std::shared_ptr<Shader> computeShader = Shader::CreateComputeShader("assets/shaders/raymarch.comp");

	m_RayMarcher = RayMarcher::Create(computeShader, camera);
	
	RaymarchObject* object1 = RaymarchObject::Create(Transform(), Material(glm::vec3(0.2f, 0, 0)), RaymarchObjectType::Sphere, 1, CombineType::Blend);
	RaymarchObject* child1 = RaymarchObject::Create(Transform(glm::vec3(-2, 0, 0), glm::vec3(0), glm::vec3(1, 0.3f, 0)), Material(glm::vec3(0, 0.2f, 0)), RaymarchObjectType::Torus, 1);
	RaymarchObject* child2 = RaymarchObject::Create(Transform(glm::vec3(2, 0, 0)), Material(glm::vec3(0, 0.1f, 0.2f)), RaymarchObjectType::Box, 1);
	
	object1->AddChild(child1);
	object1->AddChild(child2);

	PointLight light = PointLight(glm::vec3(0, 2, 0), glm::vec3(1), 2);
	m_RayMarcher->AddPointLight(light);

	m_RayMarcher->AddObject(object1);
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
	ImGui::Text("FPS: %d", static_cast<int>(1 / deltaTime));
	ImGui::Text("\nCONTROLS");
	ImGui::Text("Exit Scene: ESCAPE or BACKSPACE");
	ImGui::Text("Enter Scene: SPACE or ENTER");
	ImGui::Text("Capped FPS Off/On: V");
	ImGui::Text("Movement: W, A, S, D, E, Q");
	ImGui::End();

	ImGui::Begin("Objects");
	static int s_SelectedObjectIndex = -1;
	static int s_SelectedLightIndex = -1;

	int i = 0;
	for (auto& object : m_RayMarcher->GetObjects())
	{
		std::string objectName = "Object " + std::to_string(i);
		if (ImGui::Selectable(objectName.c_str()))
		{
			s_SelectedObjectIndex = i;
			s_SelectedLightIndex = -1;
		}

		for (auto& child : object->children)
		{
			i++;
			std::string childName = "  Child " + std::to_string(i);
			if (ImGui::Selectable(childName.c_str()))
			{
				s_SelectedObjectIndex = i;
				s_SelectedLightIndex = -1;
			}
		}

		i++;
	}

	int lightIndex = 0;
	for (auto& light : m_RayMarcher->GetPointLights())
	{
		std::string lightName = "Point Light " + std::to_string(lightIndex);
		if (ImGui::Selectable(lightName.c_str()))
		{
			s_SelectedObjectIndex = -1;
			s_SelectedLightIndex = lightIndex;
		}
		lightIndex++;
	}

	for (auto& light : m_RayMarcher->GetDirectionalLights())
	{
		std::string lightName = "Directional Light " + std::to_string(lightIndex);
		if (ImGui::Selectable(lightName.c_str()))
		{
			s_SelectedObjectIndex = -1;
			s_SelectedLightIndex = lightIndex;
		}
		lightIndex++;
	}
	ImGui::End();

	ImGui::Begin("Data");
	if (s_SelectedObjectIndex != -1)
	{
		ComputeRaymarchObject* object = &m_RayMarcher->GetComputeObjects().at(s_SelectedObjectIndex);
		
		const char* objectTypeNames[] = { "Sphere", "Box", "Torus" }; 
		int currentObjectType = static_cast<int>(object->type);
		if (ImGui::Combo("Object Type", &currentObjectType, objectTypeNames, IM_ARRAYSIZE(objectTypeNames)))
		{
			object->type = static_cast<RaymarchObjectType>(currentObjectType);
		}
		
		ImGui::DragFloat3("Position", glm::value_ptr(object->transform.position), 0.025f);
		ImGui::DragFloat3("Scale", glm::value_ptr(object->transform.scale), 0.01f, 0.01f, FLT_MAX);
		
		ImGui::DragFloat("Blend Strength", &object->blendStrength, 0.01f, 0.f, 1.f);

		const char* combineTypeNames[] = { "Blend", "Mask", "Substract" };
		int currentType = static_cast<int>(object->combineType);
		if (ImGui::Combo("Combine Type", &currentType, combineTypeNames, IM_ARRAYSIZE(combineTypeNames)))
		{
			object->combineType = static_cast<CombineType>(currentType);
		}
		
		ImGui::ColorPicker3("Color", glm::value_ptr(object->material.diffuseColor));
	}

	if (s_SelectedLightIndex != -1)
	{
		if (s_SelectedLightIndex < m_RayMarcher->GetPointLights().size())
		{
			PointLight& light = m_RayMarcher->GetPointLights().at(s_SelectedLightIndex);
			ImGui::DragFloat3("Position", glm::value_ptr(light.position), 0.025f);
			ImGui::DragFloat("Intensity", &light.intensity, 0.01f, 0.f, FLT_MAX);
			ImGui::ColorPicker3("Color", glm::value_ptr(light.color));
		}
		else
		{
			DirectionalLight& light = m_RayMarcher->GetDirectionalLights().at(s_SelectedLightIndex - m_RayMarcher->GetPointLights().size());
			ImGui::DragFloat3("Direction", glm::value_ptr(light.direction), 0.01f);
			ImGui::ColorPicker3("Color", glm::value_ptr(light.color));
		}
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
