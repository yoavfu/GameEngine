#pragma once
#include <GLFW/glfw3.h>
#include "Event.h"

namespace InputEngine
{
	class Keyboard : public Observed
	{
	public:
		static Keyboard& getInstance() // Singleton is accessed via getInstance()
		{
			static Keyboard instance; // lazy singleton, instantiated on first use
			return instance;
		}

		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		void KeyboardCallback(int key, int scancode, int action, int mods);

	private:
		Keyboard(void) // private constructor necessary to allow only 1 instance
		{
		}

		Keyboard(Keyboard const&) = delete; // prevent copies
		void operator=(Keyboard const&) = delete; // prevent assignments
	};
}


enum KeyboardKeyPressed
{
	MSG_KEY_W,
	MSG_KEY_D,
	MSG_KEY_A,
	MSG_KEY_S,
};

class KeyboardMessage : public Message
{
public:
	KeyboardMessage(KeyboardKeyPressed keyPressed) :
		Message(MSG_KEYBOARD, 0), keyPressed_(keyPressed)
	{};
	KeyboardKeyPressed keyPressed_;
};

class OnKeyboardEventListener
{
public:
	virtual void OnKeyboardEvent(const KeyboardMessage &msg) = 0;
};
