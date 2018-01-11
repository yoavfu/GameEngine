#pragma once
#include <string>
#include <glm\glm.hpp>

using namespace std;

class Shader
{
public:
	Shader(const string& vertexShader, const string& fragmentShader);
	virtual ~Shader();


	inline unsigned int GetId() const
	{
		return programID_;
	}
	void Use() const;
	// utility uniform functions
	// Sets a bool uniform (must call Use function before calling this function)
	void SetBool(const std::string &name, bool value) const;
	// Sets a int uniform (must call Use function before calling this function)
	void SetInt(const std::string &name, int value) const;
	// Sets a float uniform (must call Use function before calling this function)
	void SetFloat(const std::string &name, float value) const;
	// Sets a vec2 uniform (must call Use function before calling this function)
	void SetVec2(const std::string & name, const glm::vec2 & value) const;
	// Sets a vec2 uniform (must call Use function before calling this function)
	void SetVec2(const std::string & name, float x, float y) const;
	// Sets a vec3 uniform (must call Use function before calling this function)
	void SetVec3(const std::string & name, glm::vec3 & value) const;
	// Sets a vec3 uniform (must call Use function before calling this function)
	void SetVec3(const std::string & name, float x, float y, float z) const;
	// Sets a mat2 uniform (must call Use function before calling this function)
	void SetMat2(const std::string & name, const glm::mat2 & mat) const;
	// Sets a mat3 uniform (must call Use function before calling this function)
	void SetMat3(const std::string & name, const glm::mat3 & mat) const;
	// Sets a mat4 uniform (must call Use function before calling this function)
	void SetMat4(const std::string &name, glm::mat4& value) const;

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

