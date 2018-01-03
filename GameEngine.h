#pragma once
#include "Display.h"
#include "Camera.h"

class GameEngine
{
public:
	GameEngine();
	virtual ~GameEngine();
	void GameLoop();

private:
	Display display_;
};

