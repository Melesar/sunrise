#pragma once

#include <string>
#include <GL/glew.h>

class Texture
{
public:
	Texture(const std::string& fileName);
	virtual ~Texture();

	void Bind(unsigned int unit);

private:
	static const int MaximumTextures = 32;

	GLuint textureData;
};
