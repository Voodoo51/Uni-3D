#pragma once
#include <cstdlib>
#include <ctime>
#include "Renderer.h"

enum TileType
{
	Walkable,
	NonWalkable,
	WalkableWin
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
	void InitTilesMemory();
	void GenerateModels();
	void GenerateMap0();
	void GenerateMap1();
	void GenerateMap2();
	void FreeHandles();
	ivec2 spawn;
	Tile** tiles;
	int sizeX;
	int sizeY;
	bool change;
private:
	std::vector<Handle> handles;
};

//extern Map map;