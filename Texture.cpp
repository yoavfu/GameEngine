#include "Texture.h"
#include "stb_image.h"
#include <glad\glad.h>
#include <iostream>
#include <assert.h>

Texture::Texture(const std::string & fileName, IMAGE_FORMAT imageColors, bool flipImage)
{
	int width, height, numOfComponents;	

	glGenTextures(1, &textureID_);
	glBindTexture(GL_TEXTURE_2D, textureID_);

	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// load image, create texture and generate mipmaps
	stbi_set_flip_vertically_on_load(flipImage);
	unsigned char* imageData = stbi_load(fileName.c_str(), &width, &height, &numOfComponents, 0);

	if (imageData == nullptr)
	{
		std::cerr << "ERROR: Texture loading failed for texture: " << fileName << std::endl;
		throw("ERROR: Texture loading failed for texture: " + fileName);
	}
	else
	{
		unsigned int colorFormat = GetColorFormat(imageColors);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, colorFormat, GL_UNSIGNED_BYTE, imageData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	stbi_image_free(imageData);
}

Texture::~Texture()
{
	glDeleteTextures(1, &textureID_);
}

void Texture::Bind(unsigned int unit)
{
	assert(unit >= 0 && unit <= 31);

	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, textureID_);
}

unsigned int Texture::GetColorFormat(IMAGE_FORMAT imageFormat) const
{
	if (imageFormat == RGB)
		return GL_RGB;
	else if (imageFormat == RGBA)
		return GL_RGBA;

	return 0;
}
