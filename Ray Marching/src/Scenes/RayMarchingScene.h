#pragma once

#include "../Core/Scene.h"
#include "../Utils/Shader.h"
#include "../Objects/Quad.h"
#include "../Objects/FullscreenQuad.h"
#include "../BufferObjects/FrameBuffer.h"

class RayMarchingScene : public Scene
{
public:
	void OnCreate() override;
	void OnUpdate(double deltaTime) override;
	void OnDestroy() override;
private:
	FullscreenQuad* m_FullscreenQuad;

	Quad* m_Quad;
};