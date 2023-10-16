#include "Core/Application.h"

#include "Scenes/Ray Marching/RayMarchingScene.h"

int main()
{
	Application app = Application("Ray Marching", 1280, 720, new RayMarchingScene());
	app.Run();
}
