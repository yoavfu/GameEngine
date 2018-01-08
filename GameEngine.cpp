#include "GameEngine.h"
#include "Shader.h"
#include "Cube.h"
#include "Texture.h"

GameEngine::GameEngine() :
	camera_(glm::vec3(0.0f, 0.0f, 3.0f))
{
	camera_.RegisterMsg();
	display_.SetInputCallbacks((void *)this);
	display_.EnableDepth();
}

GameEngine::~GameEngine()
{
}

void GameEngine::GameLoop()
{
	// build and compile our shader zprogram
	// ------------------------------------
	Shader lightingShader("Resources/Lighting/1.colors.vs", "Resources/Lighting/1.colors.fs");
	Shader lampShader("Resources/Lamp/1.lamp.vs", "Resources/Lamp/1.lamp.fs");

	Texture diffuseMap("Resources/container2.png");
	Texture specularMap("Resources/container2_specular.png");

	Cube cube;
	Cube lamp;
	glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

	float lastFrame = 0.0f;

	lightingShader.Use();
	lightingShader.SetInt("material.diffuse", 0);
	lightingShader.SetInt("material.specular", 1);

	// render loop
	// -----------
	while (!display_.ShouldClose())
	{
		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		deltaTime_ = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//// render
		display_.Clear(0.1f, 0.1f, 0.1f, 0.1f);
		// be sure to activate shader when setting uniforms/drawing objects
		lightingShader.Use();
		lightingShader.SetVec3("light.position", lightPos);
		glm::vec3 position = camera_.GetPosition();
		lightingShader.SetVec3("viewPos", position);

		// light properties
		lightingShader.SetVec3("light.ambient", 0.2f, 0.2f, 0.2f);
		lightingShader.SetVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
		lightingShader.SetVec3("light.specular", 1.0f, 1.0f, 1.0f);

		// material properties
		lightingShader.SetFloat("material.shininess", 64.0f);

		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(camera_.GetZoom()), (float)Display::SCR_WIDTH / (float)Display::SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera_.GetViewMatrix();
		lightingShader.SetMat4("projection", projection);
		lightingShader.SetMat4("view", view);

		// world transformation
		glm::mat4 model;
		lightingShader.SetMat4("model", model);
		// bind diffuse map
		diffuseMap.Bind(0);
		// bind specular map
		specularMap.Bind(1);
		// render the cube
		cube.Draw();

		// also draw the lamp object
		lampShader.Use();
		lampShader.SetMat4("projection", projection);
		lampShader.SetMat4("view", view);
		model = glm::mat4();
		// change the light's position values over time (can be done anywhere in the render loop actually, but try to do it at least before using the light source positions)
		lightPos.x = 1.0f + sin(glfwGetTime()) * 2.0f;
		lightPos.y = sin(glfwGetTime() / 2.0f) * 1.0f;
		model = glm::mat4();
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
		lampShader.SetMat4("model", model);
		lamp.Draw();

		display_.Update();
	}
}

void GameEngine::Mousecallback(double xpos, double ypos)
{
	if (firstMouse_)
	{
		lastX_ = xpos;
		lastY_ = ypos;
		firstMouse_ = false;
	}

	float xoffset = xpos - lastX_;
	float yoffset = lastY_ - ypos; // reversed since y-coordinates go from bottom to top

	lastX_ = xpos;
	lastY_ = ypos;

	camera_.ProcessMouseMovement(xoffset, yoffset);
}

void GameEngine::MouseScrollCallback(double xoffset, double yoffset)
{
	camera_.ProcessMouseScroll(yoffset);
}
