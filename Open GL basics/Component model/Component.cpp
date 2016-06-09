#include "Component.h"
#include "GameObject.h"


Component::Component()
{
}


Component::~Component()
{
}

GameObject& Component::GetGameObject()
{
	return *gameObject;
}

void Component::SetGameObject(GameObject* gameObject)
{
	if (this->gameObject != nullptr) {
		return;
	}

	this->gameObject = gameObject;
}

void Component::RecieveMessage(const std::string& message)
{
}

void Component::SubscribeToMessage(const std::string& message, MessageReceiver receiver)
{
	messages._Insert_or_assign(message, receiver);
}