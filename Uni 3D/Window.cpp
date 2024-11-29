#include "Window.h"
#include <iostream>

Window window;

void Window::DeleteContext()
{
	SDL_GL_DeleteContext(context);
}

//https://thenumb.at/cpp-course/sdl2/08/08.html
void Window::Init(int _SCR_WIDTH, int _SCR_HEIGHT)
{
	SCR_WIDTH = _SCR_WIDTH;
	SCR_HEIGHT = _SCR_HEIGHT;

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	window = SDL_CreateWindow("Uni 3D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCR_WIDTH, SCR_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
	context = SDL_GL_CreateContext(window);

	SDL_SetWindowGrab(window, SDL_TRUE);
	input.Init();

	if (window == NULL)
	{
		std::cout << "Failed to create SDL window" << std::endl;
		atexit(SDL_Quit);
		return;
	}

	if (context == NULL)
	{
		std::cout << "Failed to create SDL context" << std::endl;
		atexit(SDL_Quit);
		return;
	}

	if (!gladLoadGLLoader(SDL_GL_GetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}

	//SDL_AddEventWatch(resizingEventWatcher, window);
	//SDL_SetRelativeMouseMode(SDL_TRUE);

	SDL_GL_SetSwapInterval(1);
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	//glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

	glCullFace(GL_BACK);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	std::cout << "INIT DONE!" << std::endl;
	std::cout << std::endl;

}

void Window::PollEvents()
{
	bool mouseMotion = false;

	if (!cursorVisible)
	{
	}
	else
	{
	}

	input.scrollY = 0;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_MOUSEWHEEL)
		{
			if (event.wheel.y > 0) // scroll up
			{
				input.scrollY = 1;
			}
			else if (event.wheel.y < 0) // scroll down
			{
				input.scrollY = -1;
			}
		}

		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				input.mouseButtons[0] = true;
				input.mouseButtons[1] = false;
			}
			else if (event.button.button == SDL_BUTTON_RIGHT)
			{
				input.mouseButtons[0] = false;
				input.mouseButtons[1] = true;
			}
		}
		else if (event.type == SDL_MOUSEBUTTONUP)
		{
			input.mouseButtons[0] = false;
			input.mouseButtons[1] = false;
			input.mouseButtonProcessed[0] = false;
			input.mouseButtonProcessed[1] = false;
		}
			
		if (event.key.state == SDL_PRESSED)
		{
			input.keys[event.key.keysym.sym] = true;
		}
		else if (event.key.state == SDL_RELEASED)
		{
			input.keys[event.key.keysym.sym] = false;
			input.keysProcessed[event.key.keysym.sym] = false;
		}

		if (event.type == SDL_MOUSEMOTION)
		{
			input.mouseX = event.motion.xrel;
			input.mouseY = event.motion.yrel;

			SDL_GetMouseState(&input.mouseXPos, &input.mouseYPos);
			mouseMotion = true;
		}
	}

	if (!mouseMotion)
	{
		input.mouseX = 0;
		input.mouseY = 0;
	}

}

void Window::SwapWindow()
{
	SDL_GL_SwapWindow(window);
}

void Window::SetCursorVisible(bool on)
{
	cursorVisible = on;

	if (on)
	{
		SDL_SetRelativeMouseMode(SDL_FALSE);
		SDL_WarpMouseInWindow(window, SCR_WIDTH / 2, SCR_HEIGHT / 2);
	}
	else
	{
		SDL_SetRelativeMouseMode(SDL_TRUE);
	}
}
