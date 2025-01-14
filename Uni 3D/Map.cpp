#include "Map.h"

Map map;

Tile::Tile(TileType type)
{
	this->type = type;
}

void Map::Init()
{
	srand(time(NULL));
	change = false;
	GenerateMap(5, 5);
}

void Map::GenerateMap(int sizeX, int sizeY)
{
	this->sizeX = sizeX;
	this->sizeY = sizeY;

	if (tiles != NULL)
		free(tiles);

	tiles = new Tile * [sizeX];

	for (int i = 0; i < handles.size(); i++)
		renderer.modelRenders.Remove(handles[i]);

	handles.clear();

	for (int x = 0; x < sizeX; x++)
	{
		tiles[x] = new Tile[sizeY];
		for (int y = 0; y < sizeY; y++)
		{
			int randomValue = rand() % 6;

			tiles[x][y].type = Walkable;
			/*
			if (randomValue < 3)
				tiles[x][y].type = Walkable;
			else
				tiles[x][y].type = NonWalkable;
			*/
		}
	}

	for (int x = 0; x < sizeX; x++)
	{
		for (int y = 0; y < sizeY; y++)
		{
			if (tiles[x][y].type == Walkable)
			{
				Handle handle = renderer.modelRenders.Append(ModelRender());
				renderer.modelRenders.Get(handle).pos = vec3(x * 10, 0, y * 10);
				renderer.modelRenders.Get(handle).size = vec3(10, 10, 10);
				renderer.modelRenders.Get(handle).material.color = vec3(1, 1, 1);
				handles.push_back(handle);
			}
		}
	}

	change = true;
}
