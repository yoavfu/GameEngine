#include <iostream>
#include "Display.h"
#include "Shader.h"
#include "Mesh.h"
#include "Cube.h"
#include "Texture.h"
#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

void init_opengl();


// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float deltaTime = 0.0f;

int main()
{
	init_opengl();
	Display display;
	display.EnableDepth();

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	Shader shader("./Resources/basicShader.vs", "./Resources/basicShader.fs");
	//Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));
	Cube cube;
	Texture texture("./Resources/wall.jpg", Texture::IMAGE_FORMAT::RGB, true);
	Texture texture2("./Resources/awesomeface.png", Texture::IMAGE_FORMAT::RGBA, true);
	shader.Use();
	shader.SetInt("texture1", 0);
	shader.SetInt("texture2", 1);

	float lastFrame = 0.0f;
	// render loop
	// -----------
	while (!display.ShouldClose())
	{
		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//// render
		display.Clear(0.2f, 0.3f, 0.3f, 1.0f);
		shader.Use();

		texture.Bind(0);
		texture2.Bind(1);

		// create transformations
		glm::mat4 projection = glm::perspective(glm::radians(camera.GetZoom()), (float)Display::SCR_WIDTH / (float)Display::SCR_HEIGHT, 0.1f, 100.0f);

		// camera/view transformation
		glm::mat4 view = camera.GetViewMatrix();

		shader.SetMatrix4("view", view);
		shader.SetMatrix4("projection", projection);

		for (unsigned int i = 0; i < 10; i++)
		{
			// calculate the model matrix for each object and pass it to shader before drawing
			glm::mat4 model;
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

			shader.SetMatrix4("model", model);

			cube.Draw();
		}





		//// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		//// -------------------------------------------------------------------------------
		display.Update();
	}

	return 0;
}

void init_opengl()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif
}



