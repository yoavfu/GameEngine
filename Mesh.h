#pragma once

#include <glm\glm.hpp> // holds all OpenGL type declarations
#include "Shader.h"
#include "Texture.h"
#include <string>
#include <vector>
#include <memory>

using namespace std;

struct Vertex 
{
	// position
	glm::vec3 Position;
	// normal
	glm::vec3 Normal;
	// texCoords
	glm::vec2 TexCoords;
	// tangent
	glm::vec3 Tangent;
	// bitangent
	glm::vec3 Bitangent;
};

//struct Texture 
//{
//	unsigned int id;
//	string type;
//	string path;
//};

class Mesh 
{
public:
	/*  Mesh Data  */
	vector<Vertex> vertices_;
	vector<unsigned int> indices_;
	vector<shared_ptr<Texture>> textures_;
	unsigned int VAO_;

	/*  Functions  */
	// constructor
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<shared_ptr<Texture>> textures);
	virtual ~Mesh();

	// render the mesh
	void Draw(const Shader &shader);

private:
	/*  Render data  */
	unsigned int VBO_, EBO_;

	/*  Functions    */
	// initializes all the buffer objects/arrays
	void SetupMesh();
};
