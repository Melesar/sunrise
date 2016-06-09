#include "GameObject.h"
#include "Component.h"
#include "../Components/Transform.h"
#include "../Components/Mesh.h"


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

GameObject::GameObject()
{
	AddComponent<Transform>();
}


GameObject::~GameObject()
{
}

template <class TComponentType, typename... TArgs>
TComponentType& GameObject::AddComponent(TArgs&&... args)
{
	assert(!HasComponent<TComponentType>());

	TComponentType* c = new TComponentType(std::forward<TArgs>(args)...);
	c->SetGameObject(this);

	std::unique_ptr<Component> ptr{ c };
	components.emplace_back(std::move(ptr));

	componentArray[GetComponentId<TComponentType>()] = c;
	bits[GetComponentId<TComponentType>()] = true;

	c->Init();

	return *c;
}

template <class TComponentType>
TComponentType& GameObject::GetComponent()
{
	return *componentArray[GetComponentId<TComponentType>()];
}

template <class TComponentType>
bool GameObject::HasComponent()
{
	return bits[GetComponentId<TComponentType>()];
}