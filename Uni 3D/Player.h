#pragma once
#include "Input.h"
#include "Map.h"
#include <cmath>

class Map;
class Tile;
enum TileType;

class Player
{
public:
	void Init();
	void SetMap(Map map);
	void Update();
	Handle model;
private:
	float Lerp(float a, float b, float t);
	void Move(int posX, int posY);
	bool animating;
	float t;
	vec2 pos;
	vec2 prevPos;
	Map currentMap;
};

extern Player player;
