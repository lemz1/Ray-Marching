#include "Core/Application.h"

#include "Scenes/RayMarchingScene.h"

int main()
{
	Application::Create(new RayMarchingScene());
	Application::Run();
	Application::Destroy();
}
