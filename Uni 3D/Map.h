#pragma once
#include <cstdlib>
#include <ctime>
#include "Renderer.h"

enum TileType
{
	Walkable,
	NonWalkable
};

class Tile
{
public:
	Tile() {};
	Tile(TileType type);
	TileType type;
};

class Map
{
public:
	void Init();
	Tile tiles[20][20];
};
