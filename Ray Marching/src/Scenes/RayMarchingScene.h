#pragma once

#include "Scene.h"
#include "../Utils/Shader.h"
#include "../Objects/Quad.h"
#include "../Objects/FullscreenQuad.h"
#include "../BufferObjects/FrameBuffer.h"
#include "../Events/WindowResizeEventListener.h"
#include "../Events/KeyboardEventListener.h"

class RayMarchingScene : public Scene
{
public:
	void OnCreate() override;
	void OnUpdate(double deltaTime) override;
	void OnDestroy() override;
private:
	void OnWindowResize(const WindowResizeEvent& event);
	void OnKeyboard(const KeyboardEvent& event);
private:
	bool m_IsInScene = false;

	FullscreenQuad* m_FullscreenQuad;

	Quad* m_Quad;
};