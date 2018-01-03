#include "Mouse.h"
#include "GameEngine.h"

namespace Mouse
{
	//float lastX = Display::SCR_WIDTH / 2.0f;
	//float lastY = Display::SCR_HEIGHT / 2.0f;
	//bool firstMouse = true;
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void Mouse::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	static_cast<GameEngine*>(glfwGetWindowUserPointer(window))->Mousecallback(xpos, ypos);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void Mouse::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	static_cast<GameEngine*>(glfwGetWindowUserPointer(window))->Mousecallback(xoffset, yoffset);
}
