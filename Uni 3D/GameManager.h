#pragma once
#include "Map.h"
#include "Player.h"

/*!
	Klasa zarzadzajaca przejsciami miedzy levelami.
*/
class GameManager
{
public:
	/*!
		Funkcja inicializujaca.
	*/
	void Init();
	/*!
		Funkcja ktora pozwala nam przejsc na kolejny poziom, w momencie gdy przejdziemy wszystkie poziomy ta funkcja konczy dzialanie calego programu.
	*/
	void OnGameWon();
private:
	int currentLevel;
	Map map;
	float t;
};

extern GameManager gameManager;