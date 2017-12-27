#pragma once
#include <string>
#include <glm\glm.hpp>

using namespace std;

class Shader
{
public:
	Shader(const string& vertexShader, const string& fragmentShader);
	virtual ~Shader();

	void Use() const;
	// utility uniform functions
	// Sets a bool uniform (must call Use function before calling this function
	void SetBool(const std::string &name, bool value) const;
	// Sets a int uniform (must call Use function before calling this function
	void SetInt(const std::string &name, int value) const;
	// Sets a float uniform (must call Use function before calling this function
	void SetFloat(const std::string &name, float value) const;
	// Sets a mat4 uniform (must call Use function before calling this function
	void SetMatrix4(const std::string &name, glm::mat4& value) const;

private:
	std::string LoadShaderFromFile(const std::string & fileName) const;
	void CheckShaderError(unsigned int shader, unsigned int flag, bool isProgram, const std::string & errorMessage) const;
	unsigned int CreateShader(const std::string& text, unsigned int shaderType) const;

private:
	enum SHADERS_TYPE
	{
		VERTEX_SHADER,
		FRAGMENT_SHADER,
		NUM_OF_SHADERS,
	};

	unsigned int programID_;
	unsigned int shaders_[NUM_OF_SHADERS];
};

