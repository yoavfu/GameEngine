#pragma once
#include <string>

class Texture
{
public:
	Texture(const std::string& fileName, bool flipImage = false);
	virtual ~Texture();

	void Bind(unsigned int unit);

private:
	unsigned int textureID_;
};

