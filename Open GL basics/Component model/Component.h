#pragma once
#include <string>
#include <map>

class GameObject;

class Component
{
public:
	Component();
	virtual ~Component();

	GameObject& GetGameObject();
	void SetGameObject(GameObject* gameObject);

	void RecieveMessage(const std::string& message);

	virtual void Init() = 0;
	virtual void Update() = 0;

private:

	typedef void(*MessageReceiver) ();

	void SubscribeToMessage(const std::string& message, MessageReceiver receiver);

	std::map<std::string, MessageReceiver> messages;
	GameObject* gameObject;
};

