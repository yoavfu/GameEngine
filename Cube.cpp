#include "Cube.h"
#include <glad\glad.h>
#include <iostream>

Cube::Cube()
{
	glGenVertexArrays(1, &VAO_);
	glGenBuffers(1, &VBO_);

	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO_);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_);
	glBufferData(GL_ARRAY_BUFFER, NUM_OF_CUBE_VERTICES, vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);
}

Cube::~Cube()
{
	glDeleteVertexArrays(1, &VAO_);
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
