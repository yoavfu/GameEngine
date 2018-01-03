#include "GameEngine.h"
#include "Shader.h"
#include "Cube.h"

GameEngine::GameEngine() :
	camera_(glm::vec3(0.0f, 0.0f, 3.0f))
{
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

	Cube cube;
	Cube lamp;

	float lastFrame = 0.0f;
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
		display_.Clear(0.2f, 0.3f, 0.3f, 1.0f);
		// be sure to activate shader when setting uniforms/drawing objects
		lightingShader.Use();
		lightingShader.SetVec3("objectColor", 1.0f, 0.5f, 0.31f);
		lightingShader.SetVec3("lightColor", 1.0f, 1.0f, 1.0f);

		//texture.Bind(0);
		//texture2.Bind(1);
		// view/projection/model transformations
		glm::mat4 projection = glm::perspective(glm::radians(camera_.GetZoom()), (float)Display::SCR_WIDTH / (float)Display::SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera_.GetViewMatrix();
		glm::mat4 model;
		lightingShader.SetMat4("projection", projection);
		lightingShader.SetMat4("view", view);
		// world transformation
		lightingShader.SetMat4("model", model);
		cube.Draw();

		// also draw the lamp object
		lampShader.Use();
		lampShader.SetMat4("projection", projection);
		lampShader.SetMat4("view", view);
		model = glm::mat4();
		glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
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
