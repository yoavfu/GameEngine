#pragma once
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

extern float deltaTime_;

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

// An abstract camera class that processes input and calculates the corresponding Eular Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
	// Default camera values
	static inline  const float YAW = -90.0f;
	static inline const float PITCH = 0.0f;
	static inline const float SPEED = 2.5f;
	static inline const float SENSITIVTY = 0.1f;
	static inline const float ZOOM = 45.0f;

	// Constructor with vectors
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
	// Constructor with scalar values
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

	// Returns the view matrix calculated using Eular Angles and the LookAt Matrix
	glm::mat4 GetViewMatrix();

	// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
	void ProcessKeyboard(Camera_Movement direction);

	// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
	void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);

	// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
	void ProcessMouseScroll(float yoffset);

	inline float GetZoom()
	{
		return zoom_;
	}

private:
	// Calculates the front vector from the Camera's (updated) Eular Angles
	void UpdateCameraVectors();

private:
	// Camera Attributes
	glm::vec3 position_;
	glm::vec3 front_;
	glm::vec3 up_;
	glm::vec3 right_;
	glm::vec3 worldUp_;
	// Eular Angles
	float yaw_;
	float pitch_;
	// Camera options
	float movementSpeed_;
	float mouseSensitivity_;
	float zoom_;
};

