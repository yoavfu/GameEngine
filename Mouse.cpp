#include "Mouse.h"
#include "Camera.h"

extern Camera camera;

namespace Mouse
{
	float lastX = Display::SCR_WIDTH / 2.0f;
	float lastY = Display::SCR_HEIGHT / 2.0f;
	bool firstMouse = true;
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void Mouse::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void Mouse::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}
