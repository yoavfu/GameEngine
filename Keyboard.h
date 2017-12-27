#pragma once
#include <GLFW/glfw3.h>
#include "Camera.h"

extern Camera camera;

namespace Keyboard
{
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
}

