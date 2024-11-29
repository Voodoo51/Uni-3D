#pragma once
#include <SDL2/SDL.h>

/*!
		Funkcja odpowiedzialna za czasomierz. Pozwala na zablokowanie liczby klatek gry i sprawienie aby gra działała tak samo szybko niezależnie od klatek.
*/
class Timer
{
public:
	Timer() {};
	/*!
		Funkcja inicializująca klase Timer. Pozwala na zablokowanie liczby klatek gry.
	*/
	void Init(int capLimit);

	/*!
		Funkcja zliczajaca zmienna deltaTime. Do poprawnego działania klasy Timer wymagane jest jej wywołanie.
	*/
	void Tick();

	/*!
		Funkcja pozwalająca na sprawdzenie czy w danym momencie powinna wykonać się.
	*/
	bool CanUpdate();

	/*!
		Czas pomiedzy klatkami.
	*/
	float deltaTime;

	float time;
private:
	int capLimit;
	float previous;
	float current;
};

extern Timer timer;