#pragma once
#include <SDL2/SDL.h>
#include "Window.h"
#include <map>

/*!
	Klasa pozwalająca na łatwe obsługiwanie klawiatury i myszki.
*/
class Input {
public:
	//TODO: zmienic to potem na private
	
	/*!
		Funkcja zwracająca prawdę jeżeli dany klawisz jest naciśniety. W przeciwnym wypadku zwraca fałsz.
	*/
	bool KeyPressed(int keycode);
	/*!
		Funkcja zwracająca prawdę w danej klatce w której dany klawisz został naciśniety. W przeciwnym wypadku zwraca fałsz.
	*/
	bool KeyPressedOnce(int keycode);
	/*!
		Funkcja zwracająca prawdę w danej dany guzik myszy został naciśniety. W przeciwnym wypadku zwraca fałsz.
	*/
	bool MousePressed(int left);
	/*!
		Funkcja zwracająca prawdę w danej klatce w której dany guzik myszy został naciśniety. W przeciwnym wypadku zwraca fałsz.
	*/
	bool MousePressedOnce(int left);
	/*!
		Funkcja zwracająca kierunek ruchu myszy.
	*/
	void GetMouseAxis(int& x, int& y);

	/*!
		Kierunek ruchu myszy na osi X.
	*/
	int mouseX;
	/*!
		Kierunek ruchu myszy na osi Y.
	*/
	int mouseY;
	/*!
		Pozycja kursora na osi X.
	*/
	int mouseXPos;
	/*!
		Pozycja kursora na osi Y.
	*/
	int mouseYPos;
	/*!
		Kierunek ruchu scrolla myszy.
	*/
	int scrollY;
	//static int scrollY = 0;

private:
	//friend void Window::InitWindow(int _SCR_WIDTH, int _SCR_HEIGHT);
	//static void Init();// 
	friend class Window;
	void Init();

	std::map<int, bool> keys;
	std::map<int, bool> keysProcessed;
	int mouseButtons[2];
	int mouseButtonProcessed[2];
	float currentFrame;
	float lastFrame;
};

extern Input input;