#pragma once
#include "Player.h"

Player player;

void Player::Init()
{
	model = renderer.modelRenders.Append(ModelRender());
	renderer.modelRenders.Get(model).pos = vec3(0, 20, 0);
	renderer.modelRenders.Get(model).size = vec3(10, 20, 10);
	renderer.modelRenders.Get(model).material.color = vec3(1, 0.0, 0.0);
	renderer.modelRenders.Get(model).mID = 0;

	/*
	renderer.modelRenders.Get(model).material.ambient = vec3(1.0, 0.0, 0.0);
	renderer.modelRenders.Get(model).material.diffuse = vec3(0.5, 0.0, 0.0);
	renderer.modelRenders.Get(model).material.specular = vec3(0.2, 0.2, 0.2);
	renderer.modelRenders.Get(model).material.shininess = 1.0f;
	*/
	lastMoveX = 0;
	lastMoveY = 0;

	won = false;

	layingState = Upwards;
	afterMoveState = Upwards;
	t = 2;
	animating = false;
}

void Player::SetMap(Map newMap)
{
	currentMap = newMap;

	/*
	bool positionSet = false;
	while (!positionSet)
	{
		int randomX = rand() % currentMap.sizeX;
		int randomY = rand() % currentMap.sizeY;

		if (map.tiles[randomX][randomY].type == Walkable)
		{
			//pos.x = randomX;
			//pos.y = randomY;
			containtedTiles.clear();
			containtedTiles.push_back(ivec2(randomX, randomY));
			pos = vec2(randomX, randomY);
			//renderer.modelRenders.Get(model).pos = vec3(randomX * 10, 10, randomY * 10);
			layingState = Upwards;
			afterMoveState = Upwards;
			positionSet = true;
		}
	}
	*/
	containtedTiles.clear();
	containtedTiles.push_back(currentMap.spawn);
	pos = vec2(currentMap.spawn.x, currentMap.spawn.y);
	layingState = Upwards;
	afterMoveState = Upwards;

	skipFrame = false;
	currentMap.change = false;
	won = false;
	expectedWin = false;
}

float Player::Lerp(float a, float b, float t)
{
	return (1.0 - t) * a + t * b;
}


void Player::Update()
{
	if (won)
	{
		float prevY = 15;
		float targetY = 0;

		float y = Lerp(prevY, targetY, pow(t,2));
		renderer.modelRenders.Get(model).pos.y = y;
		t += 4 * timer.deltaTime / 1000;
		fadeInOut.fadeType = In;
		if (t >= 1)
		{
			gameManager.OnGameWon();
		}
		return;
	}

	if (Camera::freeFlightOn) return; 
	if (t <= 1)
	{
		float prevX = 0;
		float prevZ = 0;
		float prevY = 0;
		float targetX = 0;
		float targetZ = 0;
		float targetY = 0;

		switch (layingState)
		{
		case Upwards:
			prevX = prevPos.x * 10;
			prevZ = prevPos.y * 10;
			prevY = 15;
			break;
		case DownSideways:
		case DownUp:
			prevY = 10;
			break;
		}

		switch (afterMoveState)
		{
		case Upwards:
			targetY = 15;
			break;
		case DownSideways:
		case DownUp:
			targetY = 10;
			break;
		}

		float x = Lerp(prevPos.x, pos.x, sqrt(t));
		float z = Lerp(prevPos.y, pos.y, sqrt(t));
		float y = 0;//float y = Lerp(prevY, targetY, sqrt(t));
		if (layingState == Upwards)
		{
			y = Lerp(prevY, targetY, pow(t, 2));
		}
		else
		{
			y = Lerp(prevY, targetY, pow(t, 1/2));
		}

		float rot = Lerp(0, 90, sqrt(t));
		renderer.modelRenders.Get(model).pos.x = x * 10;
		renderer.modelRenders.Get(model).pos.z = z * 10;
		renderer.modelRenders.Get(model).pos.y = y;// + sin(sqrt(t) * 3.1415) * 5;

		if (layingState == Upwards)
		{
			if (prevPos.x != pos.x)
				if (prevPos.x < pos.x)
					renderer.modelRenders.Get(model).rot.z = -rot * 3.1415 / 180;
				else
					renderer.modelRenders.Get(model).rot.z = rot * 3.1415 / 180;
			else
				if (prevPos.y < pos.y)
					renderer.modelRenders.Get(model).rot.x = rot * 3.1415 / 180;
				else
					renderer.modelRenders.Get(model).rot.x = -rot * 3.1415 / 180;
		}
		else if (layingState == DownSideways)
		{
			if (prevPos.x != pos.x)
				if (prevPos.x < pos.x)
					renderer.modelRenders.Get(model).rot.z = (90 * 3.1415 / 180) - rot * 3.1415 / 180;
				else
					renderer.modelRenders.Get(model).rot.z = (90 * 3.1415 / 180) + rot * 3.1415 / 180;
			else
				if (prevPos.y < pos.y)
					renderer.modelRenders.Get(model).rot.x = rot * 3.1415 / 180;
				else
					renderer.modelRenders.Get(model).rot.x = -rot * 3.1415 / 180;
		}
		else if (layingState == DownUp)
		{
			if (prevPos.x != pos.x)
				if (prevPos.x < pos.x)
					renderer.modelRenders.Get(model).rot.y = -rot * 3.1415 / 180;
				else
					renderer.modelRenders.Get(model).rot.y = rot * 3.1415 / 180;
			else
				if (prevPos.y < pos.y)
					renderer.modelRenders.Get(model).rot.x = (90 * 3.1415 / 180) + rot * 3.1415 / 180;
				else
					renderer.modelRenders.Get(model).rot.x = (90 * 3.1415 / 180) -rot * 3.1415 / 180;
		}

		t += 4 * timer.deltaTime / 1000;
		skipFrame = true;
	}
	else
	{
		won = expectedWin;
		if (won)
		{
			t = 0;
		}

		animating = false;
		
		layingState = afterMoveState;
		renderer.modelRenders.Get(model).pos.x = pos.x * 10;
		renderer.modelRenders.Get(model).pos.z = pos.y * 10;
		switch (layingState)
		{
		case Upwards:
		
			renderer.modelRenders.Get(model).pos.y = 15;

			renderer.modelRenders.Get(model).rot.x = 0;
			renderer.modelRenders.Get(model).rot.z = 0;
			renderer.modelRenders.Get(model).rot.y = 0;
			break;
		case DownSideways:
			renderer.modelRenders.Get(model).pos.y = 10;

			renderer.modelRenders.Get(model).rot.x = 0;
			renderer.modelRenders.Get(model).rot.z = 90 * 3.1415 / 180;
			renderer.modelRenders.Get(model).rot.y = 0;
			break;
		case DownUp:
			renderer.modelRenders.Get(model).pos.y = 10;

			renderer.modelRenders.Get(model).rot.x = 90 * 3.1415 / 180;
			renderer.modelRenders.Get(model).rot.z = 0;
			renderer.modelRenders.Get(model).rot.y = 0;
			break;
		}
	}

	//if (currentMap.change)
	//	SetMap(map);

	if (animating)
		return;
	if (skipFrame)
	{
		skipFrame = false;
		true;
	}

	if (input.KeyPressed(SDLK_s))
		Move(0, 1);
	else if (input.KeyPressed(SDLK_w))
		Move(0, -1);
	else if (input.KeyPressed(SDLK_a))
		Move(-1, 0);
	else if (input.KeyPressed(SDLK_d))
		Move(1, 0);
}

void Player::Move(int moveX, int moveY)
{
	//20 is max map width and height
	//if (!CanMove(moveX, moveY)) return;
	//if (pos.x + moveX < 0 || pos.x + moveX >= map.sizeX || pos.y + moveY < 0 || pos.y + moveY >= map.sizeY) return;

	bool canMove = false;	

	auto CoverOneTile = [this, &canMove](int i, int moveX, int moveY, int removeCount, bool ignoreWin = false)
		{
			containtedTiles.push_back(ivec2(containtedTiles[i].x + moveX, containtedTiles[i].y + moveY));

			for (int i = 0; i < removeCount; i++)
			{
				containtedTiles.erase(containtedTiles.begin());
			}

			if (!ignoreWin)
			{
				expectedWin = CanWin(containtedTiles[0].x, containtedTiles[0].y);
			}

			canMove = true;

			
		};

	auto CoverTwoTiles = [this, &canMove](int moveX, int moveY, int removeCount)
		{
			containtedTiles.push_back(ivec2(containtedTiles[0].x + moveX, containtedTiles[0].y + moveY));
			containtedTiles.push_back(ivec2(containtedTiles[1].x + moveX, containtedTiles[1].y + moveY));

			for (int i = 0; i < removeCount; i++)
			{
				containtedTiles.erase(containtedTiles.begin());
			}

			canMove = true;
		};

	switch (layingState)
	{
		case Upwards:
			
			//We can do that because we know that either moveX or moveY is zero
			if (CanMove(containtedTiles[0].x + moveX, containtedTiles[0].y + moveY) &&
				CanMove(containtedTiles[0].x + moveX * 2, containtedTiles[0].y + moveY * 2))
			{				
				
				CoverOneTile(0, moveX, moveY, 0, true);
				CoverOneTile(0, moveX * 2, moveY * 2, 1, true);
				/*
				containtedTiles.push_back(ivec2(containtedTiles[0].x + moveX, containtedTiles[0].y + moveY));
				containtedTiles.push_back(ivec2(containtedTiles[0].x + moveX * 2, containtedTiles[0].y + moveY * 2));
				containtedTiles.erase(containtedTiles.begin());
				canMove = true;
				*/
				
			}

			break;
		case DownSideways:
			//We are assuming that we have two tiles contained, otherwise our program crashes and tells us that something is wrong
			if (moveX != 0)
			{
				//this means that we landed on a tile that is already contained
				if (containtedTiles[0].x + moveX == containtedTiles[1].x)
				{
					if (CanMove(containtedTiles[1].x + moveX, containtedTiles[1].y))
					{
						CoverOneTile(1, moveX, 0, 2);
					}
				}
				else
				{
					if (CanMove(containtedTiles[0].x + moveX, containtedTiles[0].y))
					{
						CoverOneTile(0, moveX, 0, 2);
					}
				}
			}
			else
			{
				for (int i = 0; i < containtedTiles.size(); i++)
				{
					if (!CanMove(containtedTiles[i].x, containtedTiles[i].y + moveY))
					{
						//canMove = false;
						return;
					}
				}
				CoverTwoTiles(0, moveY, 2);
				canMove = true;
			}
			break;
		case DownUp:
			if (moveX != 0)
			{
				for (int i = 0; i < containtedTiles.size(); i++)
				{
					if (!CanMove(containtedTiles[i].x + moveX, containtedTiles[i].y))
					{
						//canMove = false;
						return;
					}
				}
				CoverTwoTiles(moveX, 0, 2);
			}
			else
			{
				if (containtedTiles[0].y + moveY == containtedTiles[1].y)
				{
					if (CanMove(containtedTiles[1].x, containtedTiles[1].y + moveY))
					{
						CoverOneTile(1, 0, moveY, 2);
					}
				}
				else
				{
					if (CanMove(containtedTiles[0].x, containtedTiles[0].y + moveY))
					{
						CoverOneTile(0, 0, moveY, 2);
					}
				}
			}
			break;
	}

	if (!canMove) return;
		prevPos.x = pos.x;
		prevPos.y = pos.y;
	lastMoveX = moveX; //Posivite: RIGHT, Negative: LEFT
	lastMoveY = moveY; //Posivite: UP, Negative: DOWN

	/*
	for (int x = 0; x < map.sizeX; x++)
	{
		for (int y = 0; y < map.sizeY; y++)
		{
			bool playerOccupied = false;
			for (int i = 0; i < containtedTiles.size(); i++)
			{
				if (x == containtedTiles[i].x && y == containtedTiles[i].y)
				{
					playerOccupied = true;
					std::cout << "O";
				}
			}
			if (map.tiles[x][y].type == Walkable && !playerOccupied)
			{
				std::cout << "-";
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	*/

	vec2 avgPos = vec2(0, 0);
	for (int i = 0; i < containtedTiles.size(); i++)
	{
		avgPos.x += containtedTiles[i].x;
		avgPos.y += containtedTiles[i].y;
	}

	avgPos.x /= (float)containtedTiles.size();
	avgPos.y /= (float)containtedTiles.size();

	pos = avgPos;

	t = 0;
	animating = true;
	/*
	if (currentMap.tiles[(int)pos.x + moveX][(int)pos.y + moveY].type == Walkable)
	{
		lastMoveX = moveX; //Posivite: RIGHT, Negative: LEFT
		lastMoveY = moveY; //Posivite: UP, Negative: DOWN
		pos.x += moveX;
		pos.y += moveY;
		t = 0;
		animating = true;
	}
	*/

	switch (layingState)
	{
	case Upwards:
		if (moveX != 0)
			afterMoveState = DownSideways;
		else
			afterMoveState = DownUp;
		break;
	case DownSideways:
		if (moveX != 0)
			afterMoveState = Upwards;
		break;
	case DownUp:
		if (moveY != 0)
			afterMoveState = Upwards;
		break;
	}
}

bool Player::CanMove(int x, int y)
{
	if (x < 0 || x >= currentMap.sizeX || y < 0 || y >= currentMap.sizeY) return false;
	if (currentMap.tiles[x][y].type == NonWalkable) return false;

	return true;
}

bool Player::CanWin(int x, int y)
{
	if (x < 0 || x >= currentMap.sizeX || y < 0 || y >= currentMap.sizeY) return false;
	if (currentMap.tiles[x][y].type != WalkableWin) return false;

	return true;
}