#pragma once
#include "Input.h"
#include "Map.h"
#include <cmath>

class Map;

class Player
{
public:
	void Init();
	void SetMap(Map map);
	void Update();
	Handle model;
private:
	float Lerp(float a, float b, float t);
	bool animating;
	float t;
	void Move(int posX, int posY);
	vec2 pos;
	vec2 prevPos;
	Map currentMap;
};
