#pragma once

class Scene
{
public:
	virtual void OnCreate() = 0;
	virtual void OnUpdate(double deltaTime) = 0;
	virtual void OnDestroy() = 0;
	//virtual void OnImGuiUpdate(float deltaTime) = 0;
};
