#pragma once
#include <GLFW/glfw3.h>
#include "Display.h"

namespace Mouse
{
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
}
