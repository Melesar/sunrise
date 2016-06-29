#pragma once
#include <string>
#include <glm/detail/type_vec2.hpp>

class Utilites
{
public:
	static std::string VectorToString(const glm::vec2 vector);
	static std::string VectorToString(const glm::vec3 vector);
	static std::string VectorToString(const glm::vec4 vector);
};
