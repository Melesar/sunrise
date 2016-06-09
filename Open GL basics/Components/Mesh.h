#pragma once

#include "glm/glm.hpp"
#include "GL/glew.h"
#include "../Utilites/obj_loader.h"
#include "../Component model/Component.h"

class Vertex
{
public:
	Vertex (const glm::vec3& position, const glm::vec2& texCoord, const glm::vec3& normal = glm::vec3(0, 0, 0))
	{
		this->position = position;
		this->texCoords = texCoord;
		this->normal = normal;
	}

	glm::vec3 GetPos()
	{
		return position;
	}

	glm::vec2 GetTexCoords()
	{
		return texCoords;
	}

	glm::vec3 GetNormal()
	{
		return normal;
	}

private:
	glm::vec3 position;
	glm::vec2 texCoords;
	glm::vec3 normal;
};

class Mesh : public Component
{
public:
	Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
	Mesh(const std::string& fileName);
	virtual ~Mesh();

	void Update() override;
	void Init() override;

private:
	Mesh(const Mesh& other);
	void operator = (const Mesh& other);

	enum
	{
		POSITION_VB,
		TEXCOORD_VB,
		INDEX_VB,
		NORMAL_VB,

		NUM_BUFFERS
	};

	IndexedModel model;

	GLuint vertexArrayObject;
	GLuint vertexArrayBuffers[NUM_BUFFERS];

	unsigned int drawCount;
};
