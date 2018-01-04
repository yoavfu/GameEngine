#include "Keyboard.h"
#include "Camera.h"

namespace InputEngine
{
	void Keyboard::key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		getInstance().KeyboardCallback(key, scancode, action, mods);
	}

	void Keyboard::KeyboardCallback(int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_W)
		{
			KeyboardMessage msg(MSG_KEY_W);
			SendMessage(msg);
		}
		if (key == GLFW_KEY_S)
		{
			KeyboardMessage msg(MSG_KEY_S);
			SendMessage(msg);
		}
		if (key == GLFW_KEY_A)
		{
			KeyboardMessage msg(MSG_KEY_A);
			SendMessage(msg);
		}
		if (key == GLFW_KEY_D)
		{
			KeyboardMessage msg(MSG_KEY_D);
			SendMessage(msg);
		}
	}
}
