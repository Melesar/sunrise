#pragma once

#include <memory>
#include <bitset>
#include <cassert>
#include <array>
#include <vector>

class Transform;
class Scene;
class Component;

class GameObject
{
public:

	template <class TComponentType, typename... TArgs>
	TComponentType& AddComponent(TArgs&&... args)
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
	TComponentType& GetComponent()
	{
		assert(HasComponent<TComponentType>());

		auto ptr(componentArray[GetComponentId<TComponentType>()]);
		return *static_cast<TComponentType*>(ptr);
	}

	template <class TComponentType>
	bool HasComponent()
	{
		return bits[GetComponentId<TComponentType>()];
	}

	bool IsActive() const;
	void SetActive(bool value);

	void Update();
	void SendMessage(const std::string& message);

	Transform& transform();

	GameObject();
	~GameObject();

	static void SetScene(Scene* scene) { GameObject::scene = scene; }
private:
	static const unsigned int MAXIMUM_COMPONENTS = 32;

	static Scene* scene;

	std::vector<std::unique_ptr<Component>> components;
	std::array<Component*, MAXIMUM_COMPONENTS> componentArray;
	std::bitset<MAXIMUM_COMPONENTS> bits;

	using ComponentID = std::size_t;

	static ComponentID GetUniqueId()
	{
		static ComponentID lastId{ 0u };
		return lastId++;
	}

	template<class TComponentType> ComponentID GetComponentId()
	{
		static_assert(std::is_base_of<Component, TComponentType>::value, "Type must inherit from Component");

		static ComponentID componentId{ GetUniqueId() };
		return componentId;
	}

	bool active;
};

