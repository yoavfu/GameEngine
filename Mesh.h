#pragma once

#include <glad/glad.h> // holds all OpenGL type declarations
#include "Shader.h"
#include <string>
#include <vector>

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

struct Texture 
{
	unsigned int id;
	string type;
	string path;
};

class Mesh 
{
public:
	/*  Mesh Data  */
	vector<Vertex> vertices_;
	vector<unsigned int> indices_;
	vector<Texture> textures_;
	unsigned int VAO_;

	/*  Functions  */
	// constructor
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
	virtual ~Mesh();

	// render the mesh
	void Draw(Shader shader);

private:
	/*  Render data  */
	unsigned int VBO_, EBO_;

	/*  Functions    */
	// initializes all the buffer objects/arrays
	void SetupMesh();
};
