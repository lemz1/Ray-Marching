#pragma once

#include "../Core/Scene.h"
#include "../Utils/Shader.h"
#include "../Utils/CameraController.h"
#include "../Objects/Quad.h"
#include "../Events/WindowResizeEventListener.h"
#include "../Events/KeyboardEventListener.h"

class RayMarchingScene : public Scene
{
public:
	void OnCreate() override;
	void OnUpdate(double deltaTime) override;
	void OnImGuiUpdate(double deltaTime) override;
	void OnDestroy() override;
private:
	void OnWindowResize(const WindowResizeEvent& event);
	void OnKeyboard(const KeyboardEvent& event);
private:
	bool m_IsInScene = true;

	CameraController m_CameraController;

	Quad* m_Quad;
};