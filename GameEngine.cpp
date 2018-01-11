#include "GameEngine.h"
#include "Shader.h"
#include "Model.h"
#include "Cube.h"

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
	Shader shader("Resources/Shaders/Model_Loading/model_loading.vs", "Resources/Shaders/Model_Loading/model_loading.fs");
	Shader lampShader("Resources/Shaders/Lamp/1.lamp.vs", "Resources/Shaders/Lamp/1.lamp.fs");
	Model nanoSuit("Resources/Model/nanosuit/nanosuit.obj"); 
	float lastFrame = 0.0f;

	Cube lamp;

	// positions all containers
	glm::vec3 modelPositions[] = {
		glm::vec3(0.7f,  0.2f,  2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
	};

	// positions of the point lights
	glm::vec3 pointLightPositions[] = {
		glm::vec3(0.7f,  0.2f,  2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3(0.0f,  0.0f, -3.0f)
	};

	// render loop
	// -----------
	while (!display_.ShouldClose())
	{
		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		deltaTime_ = currentFrame - lastFrame;
		lastFrame = currentFrame;

		display_.Clear(0.05f, 0.05f, 0.05f, 1.0f);
		shader.Use();
		glm::vec3 cameraPosition = camera_.GetPosition();
		glm::vec3 cameraFront = camera_.GetFront();
		shader.SetVec3("viewPos", cameraPosition);

		// directional light
		shader.SetVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
		shader.SetVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
		shader.SetVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
		shader.SetVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
		// point light 1
		shader.SetVec3("pointLights[0].position", pointLightPositions[0]);
		shader.SetVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
		shader.SetVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
		shader.SetVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
		shader.SetFloat("pointLights[0].constant", 1.0f);
		shader.SetFloat("pointLights[0].linear", 0.09);
		shader.SetFloat("pointLights[0].quadratic", 0.032);
		// point light 2
		shader.SetVec3("pointLights[1].position", pointLightPositions[1]);
		shader.SetVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
		shader.SetVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
		shader.SetVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
		shader.SetFloat("pointLights[1].constant", 1.0f);
		shader.SetFloat("pointLights[1].linear", 0.09);
		shader.SetFloat("pointLights[1].quadratic", 0.032);
		// point light 3
		shader.SetVec3("pointLights[2].position", pointLightPositions[2]);
		shader.SetVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
		shader.SetVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
		shader.SetVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
		shader.SetFloat("pointLights[2].constant", 1.0f);
		shader.SetFloat("pointLights[2].linear", 0.09);
		shader.SetFloat("pointLights[2].quadratic", 0.032);
		// point light 4
		shader.SetVec3("pointLights[3].position", pointLightPositions[3]);
		shader.SetVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
		shader.SetVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
		shader.SetVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
		shader.SetFloat("pointLights[3].constant", 1.0f);
		shader.SetFloat("pointLights[3].linear", 0.09);
		shader.SetFloat("pointLights[3].quadratic", 0.032);
		// spotLight
		shader.SetVec3("spotLight.position", cameraPosition);
		shader.SetVec3("spotLight.direction", cameraFront);
		shader.SetVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
		shader.SetVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
		shader.SetVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
		shader.SetFloat("spotLight.constant", 1.0f);
		shader.SetFloat("spotLight.linear", 0.09);
		shader.SetFloat("spotLight.quadratic", 0.032);
		shader.SetFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));

		// material properties
		shader.SetFloat("material.shininess", 64.0f);

		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(camera_.GetZoom()), (float)Display::SCR_WIDTH / (float)Display::SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera_.GetViewMatrix();
		shader.SetMat4("projection", projection);
		shader.SetMat4("view", view);

		// render the loaded model
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
		shader.SetMat4("model", model);
		nanoSuit.Draw(shader);


		// render the loaded model
		//for (unsigned int i = 0; i < 2; i++)
		//{
		//	glm::mat4 model;
		//	model = glm::translate(model, modelPositions[i]);
		//	model = glm::scale(model, glm::vec3(0.1f)); // Make it a smaller cube
		//	shader.SetMat4("model", model);
		//	nanoSuit.Draw(shader);
		//}

		// also draw the lamp object(s)
		//lampShader.Use();
		//lampShader.SetMat4("projection", projection);
		//lampShader.SetMat4("view", view);

		//for (unsigned int i = 0; i < 4; i++)
		//{
		//	glm::mat4 model;
		//	model = glm::translate(model, pointLightPositions[i]);
		//	model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		//	lampShader.SetMat4("model", model);
		//	lamp.Draw();
		//}

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
