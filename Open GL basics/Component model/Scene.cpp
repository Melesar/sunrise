#include "Scene.h"
#include "GameObject.h"
#include "../Components/Transform.h"
#include "../Components/Mesh.h"
#include "../Components/Camera.h"
#include "../Data/Texture.h"
#include "../Data/Shader.h"

Scene::Scene()
{
	GameObject::SetScene(this);

	GameObject* camera = new GameObject();
	camera->transform().position()[2] = -7.0f;
	camera->AddComponent<Camera>();

	GameObject* monkey = new GameObject();
	Mesh& monkeyMesh = monkey->AddComponent<Mesh>("./res/monkey3.obj");
	monkeyMesh.SetShader(new Shader("./res/basicShader"));
	monkeyMesh.SetTexture(new Texture("./res/bricks.jpg"));

	monkeyTransform = &monkey->transform();;
}

void Scene::Update()
{
	for (int i = 0; i < objects.size(); ++i) {
		objects[i]->Update();
	}

	monkeyTransform->rot1()[1] += counter;
	counter += 0.0001f;
}

void Scene::AddObject(GameObject* object)
{
	std::unique_ptr<GameObject> ptr (object);
	objects.emplace_back(std::move(ptr));
}