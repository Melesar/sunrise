#include "Scene.h"
#include "GameObject.h"
#include "../Components/Mesh.h"

Scene::Scene()
{
	GameObject monkey;
	monkey.AddComponent<Mesh>("./res/monkey3.obj");

	AddObject(monkey);
}

void Scene::Update()
{
	for (auto& obj : objects) {
		obj->Update();
	}
}

void Scene::AddObject(GameObject& object)
{
	std::unique_ptr<GameObject> ptr (&object);
	objects.emplace_back(std::move(ptr));
}