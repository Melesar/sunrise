#include "Scene.h"
#include "GameObject.h"
#include "../Components/Transform.h"
#include "../Components/Mesh.h"
#include "../Components/Camera.h"
#include "../Data/Texture.h"
#include "../Data/Shader.h"
#include "../Managers/Input.h"
#include <iostream>
#include "../Components/FreeMovement.h"

Scene::Scene()
{
	GameObject::SetScene(this);

	GameObject* camera = new GameObject();
	camera->transform().position().z = -7.0f;
	camera->AddComponent<Camera>();
	camera->AddComponent<FreeMovement>();

	GameObject* monkey = new GameObject();
	Mesh& monkeyMesh = monkey->AddComponent<Mesh>("./res/monkey3.obj");
	monkeyMesh.SetShader(new Shader("./res/basicShader"));
	monkeyMesh.SetTexture(new Texture("./res/bricks.jpg"));
}

void Scene::Update()
{
	for (int i = 0; i < objects.size(); ++i) {
		objects[i]->Update();
	}
}

void Scene::AddObject(GameObject* object)
{
	std::unique_ptr<GameObject> ptr (object);
	objects.emplace_back(std::move(ptr));
}