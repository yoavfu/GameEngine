#pragma once
#include "Keyboard.h"
#include "Mouse.h"
#include "Event.h"

class InputEngine
{
public:
	static InputEngine& getInstance() // Singleton is accessed via getInstance()
	{
		static InputEngine instance; // lazy singleton, instantiated on first use
		return instance;
	}

	Keyboard keyboardInput_;

private:
	InputEngine(void) // private constructor necessary to allow only 1 instance
	{
	}

	InputEngine(InputEngine const&) = delete; // prevent copies
	void operator=(InputEngine const&) = delete; // prevent assignments

};

