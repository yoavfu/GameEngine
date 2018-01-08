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

	// positions all containers
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

		//// render
		display_.Clear(0.1f, 0.1f, 0.1f, 0.1f);
		// be sure to activate shader when setting uniforms/drawing objects
		lightingShader.Use();
		glm::vec3 cameraPosition = camera_.GetPosition();
		glm::vec3 cameraFront = camera_.GetFront();
		lightingShader.SetVec3("light.position", cameraPosition);
		/*
		Here we set all the uniforms for the 5/6 types of lights we have. We have to set them manually and index
		the proper PointLight struct in the array to set each uniform variable. This can be done more code-friendly
		by defining light types as classes and set their values in there, or by using a more efficient uniform approach
		by using 'Uniform buffer objects', but that is something we'll discuss in the 'Advanced GLSL' tutorial.
		*/
		// directional light
		lightingShader.SetVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
		lightingShader.SetVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
		lightingShader.SetVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
		lightingShader.SetVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
		// point light 1
		lightingShader.SetVec3("pointLights[0].position", pointLightPositions[0]);
		lightingShader.SetVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
		lightingShader.SetVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
		lightingShader.SetVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
		lightingShader.SetFloat("pointLights[0].constant", 1.0f);
		lightingShader.SetFloat("pointLights[0].linear", 0.09);
		lightingShader.SetFloat("pointLights[0].quadratic", 0.032);
		// point light 2
		lightingShader.SetVec3("pointLights[1].position", pointLightPositions[1]);
		lightingShader.SetVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
		lightingShader.SetVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
		lightingShader.SetVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
		lightingShader.SetFloat("pointLights[1].constant", 1.0f);
		lightingShader.SetFloat("pointLights[1].linear", 0.09);
		lightingShader.SetFloat("pointLights[1].quadratic", 0.032);
		// point light 3
		lightingShader.SetVec3("pointLights[2].position", pointLightPositions[2]);
		lightingShader.SetVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
		lightingShader.SetVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
		lightingShader.SetVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
		lightingShader.SetFloat("pointLights[2].constant", 1.0f);
		lightingShader.SetFloat("pointLights[2].linear", 0.09);
		lightingShader.SetFloat("pointLights[2].quadratic", 0.032);
		// point light 4
		lightingShader.SetVec3("pointLights[3].position", pointLightPositions[3]);
		lightingShader.SetVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
		lightingShader.SetVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
		lightingShader.SetVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
		lightingShader.SetFloat("pointLights[3].constant", 1.0f);
		lightingShader.SetFloat("pointLights[3].linear", 0.09);
		lightingShader.SetFloat("pointLights[3].quadratic", 0.032);
		// spotLight
		lightingShader.SetVec3("spotLight.position", cameraPosition);
		lightingShader.SetVec3("spotLight.direction", cameraFront);
		lightingShader.SetVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
		lightingShader.SetVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
		lightingShader.SetVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
		lightingShader.SetFloat("spotLight.constant", 1.0f);
		lightingShader.SetFloat("spotLight.linear", 0.09);
		lightingShader.SetFloat("spotLight.quadratic", 0.032);
		lightingShader.SetFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));

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
		for (unsigned int i = 0; i < 10; i++)
		{
			// calculate the model matrix for each object and pass it to shader before drawing
			glm::mat4 model;
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			lightingShader.SetMat4("model", model);
			cube.Draw();
		}

		// also draw the lamp object(s)
		lampShader.Use();
		lampShader.SetMat4("projection", projection);
		lampShader.SetMat4("view", view);

		for (unsigned int i = 0; i < 4; i++)
		{
			glm::mat4 model;
			model = glm::translate(model, pointLightPositions[i]);
			model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
			lampShader.SetMat4("model", model);
			lamp.Draw();
		}

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
