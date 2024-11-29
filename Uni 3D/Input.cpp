#include "Input.h"
#include "Window.h"
#include <SDL2/SDL.h>

Input input;

void Input::Init()
{
	for (int i = 0; i < 1024; i++)
	{
		keys.insert({ i, false });
		keysProcessed.insert({ i, false });
	}
}

bool Input::KeyPressed(int keycode)
{
	return keys[keycode];
}

bool Input::KeyPressedOnce(int keycode)
{
	if (keysProcessed[keycode] == false && keys[keycode] == true)
	{
		keysProcessed[keycode] = true;
		return true;
	}
	return false;
}

bool Input::MousePressed(int button)
{
	if (button < 0 || button > 1) return false;

	return mouseButtons[button];
}

bool Input::MousePressedOnce(int button)
{
	if (button < 0 || button > 1) return false;

	if (mouseButtonProcessed[button] == false && mouseButtons[button] == true)
	{
		mouseButtonProcessed[button] = true;
		return true;
	}

	return false;
}

void Input::GetMouseAxis(int& x, int& y)
{
	x = mouseX;
	y = mouseY;
}


