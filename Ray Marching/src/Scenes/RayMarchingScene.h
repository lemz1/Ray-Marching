#pragma once

#include "../Core/Scene.h"
#include "../Utils/Shader.h"
#include "../Utils/CameraController.h"
#include "../Events/WindowResizeEventListener.h"
#include "../Events/KeyboardEventListener.h"
#include "../Objects/SDFObject.h"
#include "../Objects/PointLight.h"
#include "../Objects/DirectionalLight.h"
#include "../BufferObjects/StorageBuffer.h"

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
	bool m_IsInScene = false;

	CameraController m_CameraController;

	std::shared_ptr<Shader> m_ComputeShader;

	std::vector<SDFObject> m_Objects;
	std::vector<PointLight> m_PointLights;
	std::vector<DirectionalLight> m_DirectionalLights;

	StorageBuffer* m_SDFObjectsBuffer;
	StorageBuffer* m_PointLightsBuffer;
	StorageBuffer* m_DirectionalLightsBuffer;
};