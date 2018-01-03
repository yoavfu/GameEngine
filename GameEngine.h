#pragma once
#include "Display.h"
#include "Camera.h"
#include "InputEngine.h"

class GameEngine
{
public:
	GameEngine();
	virtual ~GameEngine();
	void GameLoop();
	void KeyboardCallback(int key, int scancode, int action, int mods);
	void Mousecallback(double xpos, double ypos);
	void MouseScrollCallback(double xoffset, double yoffset);

private:
	Display display_;
	InputEngine inputEngine_;
	Camera camera_;

	// TBD move to mouse class
	float lastX_ = Display::SCR_WIDTH / 2.0f;
	float lastY_ = Display::SCR_HEIGHT / 2.0f;
	bool firstMouse_ = true;
};

