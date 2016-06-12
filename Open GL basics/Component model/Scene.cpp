#include "Scene.h"
#include "GameObject.h"
#include "../Components/Transform.h"
#include "../Components/Mesh.h"
#include "../Components/Camera.h"
#include "../Data/Texture.h"
#include "../Data/Shader.h"
#include "../Managers/Input.h"
#include <iostream>

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

	monkeyTransform->rot1().y = counter;
	counter += 0.01f;

	if (Input::MouseButtonPressed(Input::MouseButton::Left)) {
		std::cout << "LMB pressed" << std::endl;
	} else if (Input::MouseButtonHold(Input::MouseButton::Left)) {
		std::cout << "LMB is held" << std::endl;
	} else if (Input::MouseButtonReleased(Input::MouseButton::Left)) {
		std::cout << "LMB released" << std::endl;
	}

	if (Input::KeyPressed(Input::KeyCode::W)) {
		std::cout << "W is pressed" << std::endl;
	} else if (Input::KeyHold(Input::KeyCode::W)) {
		std::cout << "W is hold" << std::endl;
	} else if (Input::KeyReleased(Input::KeyCode::W)) {
		std::cout << "W released" << std::endl;
	}
}

void Scene::AddObject(GameObject* object)
{
	std::unique_ptr<GameObject> ptr (object);
	objects.emplace_back(std::move(ptr));
}