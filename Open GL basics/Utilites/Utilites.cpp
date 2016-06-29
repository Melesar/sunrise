#include "Utilites.h"
#include <sstream>
#include <glm/detail/type_vec3.hpp>
#include <glm/detail/type_vec4.hpp>

std::string Utilites::VectorToString(const glm::vec2 vector)
{
	std::ostringstream stream;
	stream << "(" << vector.x << ", " << vector.y << ")" << std::endl;

	return stream.str();
}

std::string Utilites::VectorToString(const glm::vec3 vector)
{
	std::ostringstream stream;
	stream << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")" << std::endl;

	return stream.str();
}

std::string Utilites::VectorToString(const glm::vec4 vector)
{
	std::ostringstream stream;
	stream << "(" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ")" << std::endl;

	return stream.str();
}