#pragma once

#include "../Core/Scene.h"

#include "../Utils/Shader.h"

#include "../Objects/Quad.h"

class RayMarchingScene : public Scene
{
public:
	void OnCreate() override;
	void OnUpdate(double deltaTime) override;
	void OnDestroy() override;
private:
	std::shared_ptr<Shader> m_Shader;

	Quad* m_Quad;
};