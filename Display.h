#pragma once
#include <GLFW/glfw3.h>
#include <string>



class Display
{
public:
	// settings
	static const unsigned int SCR_WIDTH = 800;
	static const unsigned int SCR_HEIGHT = 600;

	Display(int width = 800, int height = 600, std::string title = "My window");
	virtual ~Display();

	void Clear(float red, float green, float blue, float alpha);
	void EnableDepth();
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	bool ShouldClose()
	{
		return glfwWindowShouldClose(window_);
	};
	GLFWwindow *GetWindow()
	{
		return window_;
	};
	void Update();

private:
	GLFWwindow * window_;
};

