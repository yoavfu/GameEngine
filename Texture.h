#pragma once
#include <string>

class Texture
{
public:
	enum IMAGE_FORMAT
	{
		RGB,
		RGBA
	};

	Texture(const std::string& fileName, IMAGE_FORMAT imageColors, bool flipImage = false);
	virtual ~Texture();

	void Bind(unsigned int unit);

private:
	unsigned int GetColorFormat(IMAGE_FORMAT imageFormat) const;

private:
	unsigned int textureID_;
};

