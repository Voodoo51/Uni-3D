#pragma once
#include "Player.h"

Player player;

void Player::Init()
{
	model = renderer.modelRenders.Append(ModelRender());
	renderer.modelRenders.Get(model).pos = vec3(0, 10, 0);
	renderer.modelRenders.Get(model).size = vec3(10, 10, 10);
	renderer.modelRenders.Get(model).material.ambient = vec3(0.2, 0.0, 0.0);
	renderer.modelRenders.Get(model).material.diffuse = vec3(0.5, 0.0, 0.0);
	renderer.modelRenders.Get(model).material.specular = vec3(0.9, 0.0, 0.0);

	t = 2;
	animating = false;
}

void Player::SetMap(Map newMap)
{
	currentMap = map;

	bool positionSet = false;
	while (!positionSet)
	{
		int randomX = rand() % currentMap.sizeX;
		int randomY = rand() % currentMap.sizeY;

		if (map.tiles[randomX][randomY].type == Walkable)
		{
			pos.x = randomX;
			pos.y = randomY;
			renderer.modelRenders.Get(model).pos = vec3(randomX * 10, 10, randomY * 10);
			positionSet = true;
		}
	}

	map.change = false;
}

float Player::Lerp(float a, float b, float t)
{
	return (1.0 - t) * a + t * b;
}


void Player::Update()
{
	if (t <= 1)
	{
		float x = Lerp(prevPos.x * 10, pos.x * 10, sqrt(t));
		float z = Lerp(prevPos.y * 10, pos.y * 10, sqrt(t));
		float rot = Lerp(0, 90, sqrt(t));
		renderer.modelRenders.Get(model).pos.x = x;
		renderer.modelRenders.Get(model).pos.z = z;
		renderer.modelRenders.Get(model).pos.y = 10 + sin(sqrt(t) * 3.1415) * 5;
		if (prevPos.x != pos.x)
			if(prevPos.x < pos.x)
				renderer.modelRenders.Get(model).rot.z = -rot * 3.1415 / 180;
			else
				renderer.modelRenders.Get(model).rot.z = rot * 3.1415 / 180;

		else
			if (prevPos.y < pos.y)
				renderer.modelRenders.Get(model).rot.x = rot * 3.1415 / 180;
			else
				renderer.modelRenders.Get(model).rot.x = -rot * 3.1415 / 180;

		t += 4 * timer.deltaTime / 1000;

	}
	else
	{
		prevPos.x = pos.x;
		prevPos.y = pos.y;
		animating = false;
		renderer.modelRenders.Get(model).pos.x = pos.x * 10;
		renderer.modelRenders.Get(model).pos.z = pos.y * 10;
		renderer.modelRenders.Get(model).pos.y = 10;
		renderer.modelRenders.Get(model).rot.x = 0;
		renderer.modelRenders.Get(model).rot.z = 0;
	}

	if (map.change)
		SetMap(map);

	if (animating)
		return;
	if (input.KeyPressed(SDLK_s))
		Move(pos.x, pos.y + 1);
	else if (input.KeyPressed(SDLK_w))
		Move(pos.x, pos.y - 1);
	else if (input.KeyPressed(SDLK_a))
		Move(pos.x - 1, pos.y);
	else if (input.KeyPressed(SDLK_d))
		Move(pos.x + 1, pos.y);
}

void Player::Move(int posX, int posY)
{
	//20 is max map width and height
	if (posX < 0 || posX >= 20 || posY < 0 || posY >= 20) return;

	if (currentMap.tiles[posX][posY].type == Walkable)
	{
		pos.x = posX;
		pos.y = posY;
		t = 0;
		animating = true;
	}
}