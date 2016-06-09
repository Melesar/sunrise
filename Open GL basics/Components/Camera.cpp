#include "Camera.h"
#include "glm/gtx/transform.hpp"


Camera::Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar)
{
	perspective = glm::perspective(fov, aspect, zNear, zFar);
	position = pos;
	forwardDirection = glm::vec3(0, 0, 1);
	upDirection = glm::vec3(0, 1, 0);
}

glm::mat4 Camera::GetViewProjection() const
{
	return perspective * lookAt(position, position + forwardDirection, upDirection);
}