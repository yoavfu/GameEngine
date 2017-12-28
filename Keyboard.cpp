#include "Keyboard.h"
#include "Camera.h"

void Keyboard::key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);


	if (key == GLFW_KEY_W)
		camera_.ProcessKeyboard(FORWARD);
	if (key == GLFW_KEY_S)
		camera_.ProcessKeyboard(BACKWARD);
	if (key == GLFW_KEY_A)
		camera_.ProcessKeyboard(LEFT);
	if (key == GLFW_KEY_D)
		camera_.ProcessKeyboard(RIGHT);
}
