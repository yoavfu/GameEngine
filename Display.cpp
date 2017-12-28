#include <glad/glad.h>
#include "Display.h"
#include "Mouse.h"
#include "Keyboard.h"
#include <iostream>


Display::Display(int width, int height, std::string title)
{
	// glfw window creation
	// --------------------
	window_ = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (window_ == nullptr)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		throw("Failed to create GLFW window");
	}
	glfwMakeContextCurrent(window_);
	glfwSetFramebufferSizeCallback(window_, framebuffer_size_callback);
	glfwSetKeyCallback(window_, Keyboard::key_callback);
	glfwSetCursorPosCallback(window_, Mouse::mouse_callback);
	glfwSetScrollCallback(window_, Mouse::scroll_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		throw("Failed to initialize GLAD");
	}
}


Display::~Display()
{
	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
}

//// render
//// ------
void Display::Clear(float red, float green, float blue, float alpha)
{
	glClearColor(red, green, blue, alpha);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// configure global opengl state
// -----------------------------
void Display::EnableDepth()
{
	glEnable(GL_DEPTH_TEST);
}

//// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
//// -------------------------------------------------------------------------------
void Display::Update()
{
	glfwSwapBuffers(window_);
	glfwPollEvents();
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void Display::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}
