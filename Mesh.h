#pragma once
#include <glm\glm.hpp>

struct Vertex
{
public:
	//glm::vec3 vertcies;
	float x, y, z, texCoordX, texCoordY;
};

struct Indice
{
public:
	static size_t GetSize()
	{
		return 3;
	};

public:
	int a, b, c;
};

class Mesh
{
public:
	Mesh(Vertex *vertices, size_t numOfVertices);
	Mesh(Vertex *vertices, size_t numOfVertices, Indice * indices, size_t numOfIndices);
	virtual ~Mesh();

	void Draw();

private:
	bool indiceMode_ = false;
	unsigned int VBO_, VAO_, EBO_;
	unsigned int drawCount_;
};

