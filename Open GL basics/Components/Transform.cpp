#include "Transform.h"
#include "glm/gtx/transform.hpp"


glm::mat4 Transform::GetModelMatrix() const
{
	glm::mat4 posMatrix = glm::translate(pos);
	glm::mat4 scaleMatrix = glm::scale(scale);

	return posMatrix * rotationMatrix() * scaleMatrix;
}

void Transform::Init()
{
}

void Transform::Update()
{
}

glm::vec3 Transform::forward()
{
	glm::vec4 result = rotationMatrix() * glm::vec4(0, 0, 1, 0);
	return glm::vec3(result.x, result.y, result.z);
}

glm::vec3 Transform::up()
{
	glm::vec4 result = rotationMatrix() * glm::vec4(0, 1, 0, 0);
	return glm::vec3(result.x, result.y, result.z);
}

glm::vec3 Transform::left()
{
	glm::vec4 result = rotationMatrix() * glm::vec4(1, 0, 0, 0);
	return glm::vec3(result.x, result.y, result.z);
}

glm::mat4 Transform::rotationMatrix() const
{
	glm::mat4 rotXMatrix = glm::rotate(rot.x, glm::vec3(1, 0, 0));
	glm::mat4 rotYMatrix = glm::rotate(rot.y, glm::vec3(0, 1, 0));
	glm::mat4 rotZMatrix = glm::rotate(rot.z, glm::vec3(0, 0, 1));

	return rotZMatrix * rotYMatrix * rotXMatrix;
}