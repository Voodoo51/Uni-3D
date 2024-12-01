#pragma once

#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <iostream>
#include <string>
#include <map>
#include "Input.h"

/*!
	Klasa pozwalająca na zarządznie oknem.
*/
class Window
{
public:
	/*!
		Funkcja inicializująca klasę Window. Pozwala na wybranie rozmiaru okna.
	*/
	void Init(int _SCR_WIDTH, int _SCR_HEIGHT);
	/*!
		Funkcja zczytująca eventy(np. jaki klawisz nacisnąl użytkownik).
	*/
	void PollEvents();
	/*!
		Funkcja aktualizująca okno grafiką OpenGL.
	*/
	void SwapWindow();
	/*!
		Funkcja usuwająca kontekst OpenGL.
	*/
	void DeleteContext();
	/*!
		Funkcja ustawiająca kursor na widoczny lub niewidoczny.
	*/
	void SetCursorVisible(bool on);
	/*!
		Szerokość okna.
	*/
	int SCR_WIDTH;
	/*!
		Wysokość okna.
	*/
	int SCR_HEIGHT;
	
	SDL_Event event; //pozniej to zmienic
	/*!
		Zmienna ustalająca czy program powinien się przerwać.
	*/
	bool quit;
private:
	friend class Paint;
	friend class Renderer;
	SDL_Window* window;
	SDL_GLContext context;
	bool cursorVisible;
	//static SDL_Event event;
};

extern Window window;

