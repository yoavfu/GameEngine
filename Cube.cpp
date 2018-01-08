#include "Cube.h"
#include <glad\glad.h>
#include <iostream>

unsigned int Cube::VBO_ = 0;

Cube::Cube()
{
	glGenVertexArrays(1, &VAO_);
	bool firstCube = false;
	if (VBO_ == 0)
	{
		glGenBuffers(1, &VBO_);
		firstCube = true;
	}

	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO_);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_);

	if (firstCube)
		glBufferData(GL_ARRAY_BUFFER, NUM_OF_CUBE_VERTICES, vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	if (firstCube)
	{
		// normal attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		// tex coords attribute
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);
	}

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);
}

Cube::~Cube()
{
	glDeleteVertexArrays(1, &VAO_);
	glDeleteBuffers(1, &VBO_);
}

void Cube::Draw()
{
	glBindVertexArray(VAO_);
	if (indiceMode_)
		glDrawElements(GL_TRIANGLES, NUM_OF_CUBE_VERTEX, GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(GL_TRIANGLES, 0, NUM_OF_CUBE_VERTEX);
	glBindVertexArray(0);
}
