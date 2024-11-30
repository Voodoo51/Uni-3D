#pragma once
#include "Player.h"

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
//BRB
void Player::SetMap(Map map)
{
	currentMap = map;

	bool positionSet = false;
	while (!positionSet)
	{
		int randomX = rand() % 20;
		int randomY = rand() % 20;

		if (map.tiles[randomX][randomY].type == Walkable)
		{
			pos.x = randomX;
			pos.y = randomY;
			renderer.modelRenders.Get(model).pos = vec3(randomX * 10, 10, randomY * 10);
			positionSet = true;
		}
	}
}

float Player::Lerp(float a, float b, float t)
{
	return a + t * (b - a);
}


void Player::Update()
{
	if (t <= 1)
	{
		auto x = Lerp(prevPos.x * 10, pos.x * 10, sqrt(t));
		auto z = Lerp(prevPos.y * 10, pos.y * 10, sqrt(t));
		renderer.modelRenders.Get(model).pos.x = x;
		renderer.modelRenders.Get(model).pos.z = z;
		renderer.modelRenders.Get(model).pos.y = 10 + sin(sqrt(t) * 3.1415) * 5;
		t += 4 * timer.deltaTime / 1000;

	}
	else
	{
		animating = false;
		renderer.modelRenders.Get(model).pos.x = pos.x * 10;
		renderer.modelRenders.Get(model).pos.z = pos.y * 10;
		renderer.modelRenders.Get(model).pos.y = 10;
	}

	if (animating)
		return;
	if (input.KeyPressedOnce(SDLK_w))
		Move(pos.x, pos.y + 1);
	if (input.KeyPressedOnce(SDLK_s))
		Move(pos.x, pos.y - 1);
	if (input.KeyPressedOnce(SDLK_a))
		Move(pos.x - 1, pos.y);
	if (input.KeyPressedOnce(SDLK_d))
		Move(pos.x + 1, pos.y);
}

void Player::Move(int posX, int posY)
{
	//20 is max map width and height
	if (posX < 0 || posX >= 20 || posY < 0 || posY > 20)
		return;

	if (currentMap.tiles[posX][posY].type == Walkable)
	{
		prevPos.x = pos.x;
		prevPos.y = pos.y;
		pos.x = posX;
		pos.y = posY;
		renderer.modelRenders.Get(model).pos = vec3(posX * 10, 10, posY * 10);
		t = 0;
		animating = true;
	}
}