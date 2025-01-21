#pragma once
#include "Renderer.h"

/*!
	Rodzaj efektu (brak, in, out)
*/
enum FadeType
{
	None,
	In,
	Out
};

/*!
	Klasa odpowiedzialna za efekt fade in/fade out.
*/
class FadeInOut
{
public:
	FadeInOut()
	{
		Reset();
	}

	/*!
		Funkcja wykonywujaca efekt.
	*/
	void Update();

	/*!
		Rodzaj efektu (brak, in, out)
	*/
	FadeType fadeType;
private:
	void Reset();
	float t;
};

extern FadeInOut fadeInOut;