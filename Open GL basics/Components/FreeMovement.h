#pragma once
#include "../Component model/Component.h"
#include <glm/detail/type_vec2.hpp>

class Camera;

class FreeMovement : public Component
{
public:

	float speed = 10.0f;
	float mouseSpeed = 3.2f;

	void Init() override;
	void Update() override;

private:
	glm::vec2 previousMousePos;

	Transform* transformCache;
	Camera* camera;

	float verticalBorder = 0.2f;
	float horizontalBorder = 0.2f;

	void UpdatePosition();
	void UpdateRotation();

	glm::vec2 MouseDelta();
};
