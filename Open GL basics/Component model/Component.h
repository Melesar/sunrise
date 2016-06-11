#pragma once
#include <string>
#include <map>

#include "GameObject.h"

class Component
{
public:
	Component();
	virtual ~Component();

	template<class TComponentType>
	TComponentType& GetComponent()
	{
		return gameObject->GetComponent<TComponentType>();
	}

	GameObject& GetGameObject();
	void SetGameObject(GameObject* gameObject);

	void RecieveMessage(const std::string& message);

	virtual void Init() = 0;
	virtual void Update() = 0;

private:

	typedef void(*MessageReceiver) ();

	void SubscribeToMessage(const std::string& message, MessageReceiver receiver);

	std::map<std::string, MessageReceiver> messages;

protected:

	GameObject* gameObject;
};

