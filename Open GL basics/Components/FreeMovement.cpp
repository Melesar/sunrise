#include "FreeMovement.h"
#include "../Managers/Input.h"
#include "Transform.h"
#include "../Managers/Time.h"
#include <iostream>
#include "../Utilites/Utilites.h"
#include "Camera.h"
#include "glm/gtx/transform.hpp"


typedef Input::KeyCode KeyCode;
typedef Input::MouseButton MouseButton;

void FreeMovement::Init()
{
	previousMousePos = Input::mouseCoords();
	transformCache = &gameObject->transform();
	camera = Camera::mainCamera;
}

void FreeMovement::Update()
{
	UpdatePosition();
	UpdateRotation();
}

void FreeMovement::UpdatePosition()
{
	if (Input::KeyHold(KeyCode::S)) {
		transformCache->position() -= speed * transformCache->forward() * Time::delta();
	}

	if (Input::KeyHold(KeyCode::W)) {
		transformCache->position() += speed * transformCache->forward() * Time::delta();
	}

	if (Input::KeyHold(KeyCode::A)) {
		transformCache->position() += speed * transformCache->left() * Time::delta();
	}

	if (Input::KeyHold(KeyCode::D)) {
		transformCache->position() -= speed * transformCache->left() * Time::delta();
	}
}

void FreeMovement::UpdateRotation()    
{
	glm::vec2 mouseDelta = MouseDelta();
	float horizontalAngle = mouseSpeed * Time::delta() * mouseDelta.x;
	float verticalAngle = mouseSpeed * Time::delta() * mouseDelta.y;

	transformCache->rotation().y -= horizontalAngle;
	transformCache->rotation().x += verticalAngle;

	previousMousePos = Input::mouseCoords();
}

glm::vec2 FreeMovement::MouseDelta()
{
	glm::vec2 mouseCoords = Input::mouseCoords();
	return glm::vec2(mouseCoords.x - previousMousePos.x, mouseCoords.y - previousMousePos.y);
	/*mouseCoords.x /= camera->cameraRect().w;
	mouseCoords.y /= camera->cameraRect().h;

	float deltaX = mouseCoords.x > horizontalBorder && mouseCoords.x < 1 - horizontalBorder ? 1 : 0;
	float deltaY = mouseCoords.y > verticalBorder && mouseCoords.y < 1 - verticalBorder ? 1 : 0;

	return glm::vec2(deltaX, deltaY);*/
}