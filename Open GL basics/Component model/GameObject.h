#pragma once

#include <memory>
#include <cassert>
#include <bitset>
#include <array>
#include "Component.h"
#include <vector>

class GameObject
{
public:

	template<class TComponentType, class... TArgs> TComponentType& AddComponent(TArgs&&... args);
	template<class TComponentType>				   TComponentType& GetComponent();
	template<class TComponentType>				   bool			   HasComponent();

	bool IsActive() const;
	void SetActive(bool value);

	void Update();
	void SendMessage(const std::string& message);

	GameObject();
	~GameObject();

private:
	static const unsigned int MAXIMUM_COMPONENTS = 32;

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

