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
	void GenerateMap(int sizeX, int sizeY);
	Tile** tiles;
	int sizeX;
	int sizeY;
	bool change;
private:
	std::vector<Handle> handles;
};

extern Map map;