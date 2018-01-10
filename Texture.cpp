#include "Texture.h"
#include "stb_image.h"
#include <glad\glad.h>
#include <iostream>
#include <assert.h>

Texture::Texture(const std::string & fileName, bool flipImage) :
	path_(fileName)
{
	LoadTexture(fileName, flipImage);
}

Texture::Texture(const std::string & fileName, const std::string & type, bool flipImage) :
	path_(fileName), type_(type)
{
	LoadTexture(fileName, flipImage);
}

Texture::~Texture()
{
	glDeleteTextures(1, &id_);
}

void Texture::Bind(unsigned int unit)
{
	assert(unit >= 0 && unit <= 31);

	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, id_);
}

void Texture::LoadTexture(const std::string & fileName, bool flipImage)
{
	int width, height, numOfComponents;
	// load image, create texture and generate mipmaps
	stbi_set_flip_vertically_on_load(flipImage);
	unsigned char* imageData = stbi_load(fileName.c_str(), &width, &height, &numOfComponents, 0);

	if (imageData == nullptr)
	{
		std::cerr << "ERROR: Texture loading failed for texture: " << fileName << std::endl;
		stbi_image_free(imageData);
		throw("ERROR: Texture loading failed for texture: " + fileName);
	}
	else
	{
		glGenTextures(1, &id_);

		GLenum format;
		if (numOfComponents == 1)
			format = GL_RED;
		else if (numOfComponents == 3)
			format = GL_RGB;
		else if (numOfComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, id_);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, imageData);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(imageData);
	}
}

