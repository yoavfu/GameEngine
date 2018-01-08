#pragma once
#include <glm\glm.hpp>
#include <string>



class Material
{
public:
	Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess) :
		ambient_(ambient), diffuse_(diffuse), specular_(specular), shininess_(shininess)
	{
	}
	virtual ~Material();

	glm::vec3 ambient_;
	glm::vec3 diffuse_;
	glm::vec3 specular_;
	float shininess_;

	const std::string AMBIENT_NAME = ".ambient";
	const std::string DIFFUSE_NAME = ".diffuse";
	const std::string SPECULAR_NAME = ".Specular";
	const std::string SHININESS_NAME = ".shininess";

};

class CyanPlastic : public Material
{
public:
	CyanPlastic() :
		Material(glm::vec3(0.0f, 0.1f, 0.06f), glm::vec3(0.0f, 0.50980392f, 0.50980392f), glm::vec3(0.50196078f, 0.50196078f, 0.50196078f), 32.0f)
	{
	}
};

class Emerald : public Material
{
public:
	Emerald() :
		Material(glm::vec3(0.0215f, 0.1745f, 0.0215f), glm::vec3(0.07568f, 0.61424f, 0.07568f), glm::vec3(0.633f, 0.727811f, 0.633), 32.0f)
	{
	}
};