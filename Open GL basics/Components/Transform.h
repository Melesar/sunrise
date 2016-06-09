#pragma once

#include "glm/glm.hpp"

class Transform
{
public:
	Transform(const glm::vec3& pos = glm::vec3(), const glm::vec3& rot = glm::vec3(),
		const glm::vec3& scale = glm::vec3(1, 1, 1))
		: pos(pos), rot(rot), scale(scale) {}

	glm::mat4 GetModelMatrix() const;


	glm::vec3& position()
	{
		return pos;
	}

	void set_pos(const glm::vec3& highp_vec3)
	{
		pos = highp_vec3;
	}

	glm::vec3& rot1()
	{
		return rot;
	}

	void set_rot(const glm::vec3& highp_vec3)
	{
		rot = highp_vec3;
	}

	glm::vec3& scale1()
	{
		return scale;
	}

	void set_scale(const glm::vec3& highp_vec3)
	{
		scale = highp_vec3;
	}

private:
	glm::vec3 pos;
	glm::vec3 rot;
	glm::vec3 scale;
};

