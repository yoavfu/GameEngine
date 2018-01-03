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
	void Mousecallback(double xpos, double ypos);
	void MouseScrollCallback(double xoffset, double yoffset);

private:
	Display display_;
	Camera camera_;

	// TBD move to mouse class
	float lastX_ = Display::SCR_WIDTH / 2.0f;
	float lastY_ = Display::SCR_HEIGHT / 2.0f;
	bool firstMouse_ = true;
};

