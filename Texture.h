#pragma once
#include <string>

class Texture
{
public:
	Texture(const std::string& fileName, bool flipImage = false);
	Texture(const std::string& fileName, const std::string& type, bool flipImage = false);
	virtual ~Texture();

	void Bind(unsigned int unit);
	inline const std::string& GetType() const
	{
		return type_;
	}

	inline const std::string& GetPath() const
	{
		return path_;
	}

private:
	void LoadTexture(const std::string& fileName, bool flipImage);

	unsigned int id_;
	std::string path_;
	std::string type_;
};

