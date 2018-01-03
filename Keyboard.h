#pragma once
#include <GLFW/glfw3.h>
#include "Event.h"

class Keyboard : public Observed
{
public:
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void KeyboardCallback(int key, int scancode, int action, int mods);
};

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
