#include "GameManager.h"

GameManager gameManager;

void GameManager::Init()
{
	map.GenerateMap0();
	player.SetMap(map);

	currentLevel = 0;
	t = 0;
}

void GameManager::OnGameWon()
{
	if (currentLevel < 3)
	{
		map.FreeHandles();
	}

	if (currentLevel == 0)
	{
		map.GenerateMap1();
	}

	if (currentLevel == 1)
	{
		map.GenerateMap2();
	}

	player.SetMap(map);
	currentLevel++;

	if (currentLevel >= 3)
	{
		window.quit = true;
	}
}