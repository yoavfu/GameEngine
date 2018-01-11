#include "Shader.h"
#include <glad\glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <fstream> 
#include <iostream>


Shader::Shader(const string& vertexShader, const string& fragmentShader)
{
	programID_ = glCreateProgram();
	shaders_[VERTEX_SHADER] = CreateShader(LoadShaderFromFile(vertexShader), GL_VERTEX_SHADER);
	shaders_[FRAGMENT_SHADER] = CreateShader(LoadShaderFromFile(fragmentShader), GL_FRAGMENT_SHADER);

	for (unsigned int &shader : shaders_)
		glAttachShader(programID_, shader);

	glLinkProgram(programID_);
	CheckShaderError(programID_, GL_LINK_STATUS, true, "Error: Program linking failed!");
	CheckShaderError(programID_, GL_VALIDATE_STATUS, true, "Error: Program is invalid!");

	// delete the shaders as they're linked into our program now and no longer necessery
	for (unsigned int &shader : shaders_)
		glDeleteShader(shader);
}


Shader::~Shader()
{
	for (GLuint &shader : shaders_)
		glDetachShader(programID_, shader);

	glDeleteProgram(programID_);
}

void Shader::Use() const
{
	glUseProgram(programID_);
}

std::string Shader::LoadShaderFromFile(const std::string& fileName) const
{
	string shaderCode;

	try
	{
		std::ifstream shaderFile(fileName);
		// ensure ifstream objects can throw exceptions:
		shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		shaderFile.seekg(0, std::ios::end);
		shaderCode.reserve(shaderFile.tellg());
		shaderFile.seekg(0, std::ios::beg);

		shaderCode.assign((std::istreambuf_iterator<char>(shaderFile)),
			std::istreambuf_iterator<char>());

		shaderFile.close();
	}
	catch (std::ifstream::failure e)
	{
		std::cerr <<  "ERROR loading shader: " << std::endl;
	}

	return shaderCode;
}

void Shader::CheckShaderError(unsigned int shader, unsigned int flag, bool isProgram, const std::string& errorMessage) const
{
	int success = 0;
	char error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
		throw(errorMessage + ": '" + error + "'");
	}
}

unsigned int Shader::CreateShader(const std::string & text, unsigned int shaderType) const
{
	unsigned int shader = glCreateShader(shaderType);
	if (shader == 0)
		std::cerr << "Error: Shader creation failed!" << std::endl;

	const char* shaderSourceStrings[1];
	int shaderSourceStringsLength[1];

	shaderSourceStrings[0] = text.c_str();
	shaderSourceStringsLength[0] = text.length();

	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringsLength);
	glCompileShader(shader);
	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed!");

	return shader;
}

// Sets a bool uniform (must call Use function before calling this function)
void Shader::SetBool(const std::string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(programID_, name.c_str()), (int)value);
}
// Sets a int uniform (must call Use function before calling this function)
void Shader::SetInt(const std::string &name, int value) const
{
	glUniform1i(glGetUniformLocation(programID_, name.c_str()), value);
}
// Sets a float uniform (must call Use function before calling this function)
void Shader::SetFloat(const std::string &name, float value) const
{
	glUniform1f(glGetUniformLocation(programID_, name.c_str()), value);
}
// Sets a vec2 uniform (must call Use function before calling this function)
void Shader::SetVec2(const std::string &name, const glm::vec2 &value) const
{
	glUniform2fv(glGetUniformLocation(programID_, name.c_str()), 1, &value[0]);
}
void Shader::SetVec2(const std::string &name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(programID_, name.c_str()), x, y);
}
// Sets a vec3 uniform (must call Use function before calling this function)
void Shader::SetVec3(const std::string & name, glm::vec3& value) const
{
	glUniform3fv(glGetUniformLocation(programID_, name.c_str()), 1, &value[0]);
}
// Sets a vec3 uniform (must call Use function before calling this function)
void Shader::SetVec3(const std::string &name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(programID_, name.c_str()), x, y, z);
}
// Sets a mat2 uniform (must call Use function before calling this function)
void Shader::SetMat2(const std::string &name, const glm::mat2 &mat) const
{
	glUniformMatrix2fv(glGetUniformLocation(programID_, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// Sets a mat3 uniform (must call Use function before calling this function)
void Shader::SetMat3(const std::string &name, const glm::mat3 &mat) const
{
	glUniformMatrix3fv(glGetUniformLocation(programID_, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// Sets a mat4 uniform (must call Use function before calling this function)
void Shader::SetMat4(const std::string & name, glm::mat4& value) const
{
	glUniformMatrix4fv(glGetUniformLocation(programID_, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
