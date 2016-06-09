#include "Texture.h"
#include "cassert"
#include <iostream>
#include "../Utilites/stb_image.h"

Texture::Texture(const std::string& fileName)
{
	int width, height, numComponents;
	auto imageData = stbi_load(fileName.c_str(), &width, &height, &numComponents, 4);

	if (imageData == nullptr)
	{
		std::cerr <<  "Texture loading failed: " << fileName << std::endl;
	}

	//Выделение памяти и привязка текстуры
	glGenTextures(1, &textureData);
	glBindTexture(GL_TEXTURE_2D, textureData);

	//Установка параметров рястяжения тестуры
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//Установка параметров интреполяции при несоответствии размеров отрисованной текстуры её изначальным размерам.
	//Например, такое случается при повороте, когда текстура становится меньше, или при масштабировании, когда она становится
	//больше
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

	stbi_image_free(imageData);
}

Texture::~Texture()
{
	glDeleteTextures(1, &textureData);
}

void Texture::Bind(unsigned int unit)
{
	assert(unit >= 0 && unit < MaximumTextures);

	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, textureData);
}