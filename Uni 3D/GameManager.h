#pragma once
#include "Map.h"
#include "Player.h"

class GameManager
{
public:
	void Init();
	void OnGameWon();
private:
	int currentLevel;
	Map map;
	float t;
};

extern GameManager gameManager;