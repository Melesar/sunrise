#pragma once
#include <vector>
#include <memory>

class GameObject;
class Transform;

class Scene
{
public:
	Scene();
	void Update();
	void AddObject(GameObject* object);

private:
	std::vector<std::unique_ptr<GameObject>> objects;

	Transform* monkeyTransform;
	float counter = 0.0f;
};
