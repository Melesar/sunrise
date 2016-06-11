#include "Component.h"
#include "../Components/Transform.h"
#include "Scene.h"

Scene* GameObject::scene;

bool GameObject::IsActive() const
{
	return active;
}

void GameObject::SetActive(bool value)
{
	active = value;
}

void GameObject::Update()
{
	for(auto& component : components) {
		component->Update();
	}
}

void GameObject::SendMessage(const std::string& message)
{

}

Transform& GameObject::transform()
{
	return GetComponent<Transform>();
}

GameObject::GameObject()
{
	scene->AddObject(this);
	AddComponent<Transform>();
}


GameObject::~GameObject()
{
}



