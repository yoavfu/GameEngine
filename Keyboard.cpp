#include "Keyboard.h"
#include "Camera.h"
#include "GameEngine.h"

void Keyboard::key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	static_cast<GameEngine*>(glfwGetWindowUserPointer(window))->KeyboardCallback(key, scancode, action, mods);
}
