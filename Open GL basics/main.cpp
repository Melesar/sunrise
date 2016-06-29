#include "Component model/Scene.h";
#include "Component model/GameObject.h"
#include "Managers/Application.h"

int main()
{
	Application::Start();
	Scene scene;

	while (Application::IsActive()) {
		scene.Update();
		Application::Update();
	}

	return 0;
}