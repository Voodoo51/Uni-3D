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
	GenerateMap2();
	//GenerateMap(5, 5);
}

void Map::GenerateMap(int sizeX, int sizeY)
{
	this->sizeX = sizeX;
	this->sizeY = sizeY;

	if (tiles != NULL)
		free(tiles);

	tiles = new Tile * [sizeX];


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

	GenerateModels();
	
	change = true;
}

void Map::InitTilesMemory()
{
	if (tiles != NULL)
		free(tiles);

	tiles = new Tile * [sizeX];

	for (int x = 0; x < sizeX; x++)
	{
		tiles[x] = new Tile[sizeY];
		for (int y = 0; y < sizeY; y++)
		{
			tiles[x][y].type = NonWalkable;
		}
	}
}

void Map::GenerateModels()
{
	FreeHandles();

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
}

void Map::GenerateMap0()
{
	sizeX = 10;
	sizeY = 6;
	spawn = ivec2(0, 0);

	InitTilesMemory();

	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			tiles[x][y].type = Walkable;
		}
	}

	for (int x = 1; x < 6; x++)
	{
		for (int y = 1; y < 4; y++)
		{
			tiles[x][y].type = Walkable;
		}
	}

	for (int x = 6; x < 9; x++)
	{
		for (int y = 2; y < 6; y++)
		{
			tiles[x][y].type = Walkable;
		}
	}

	for (int x = 5; x < 10; x++)
	{
		for (int y = 3; y < 5; y++)
		{
			tiles[x][y].type = Walkable;
		}
	}

	tiles[7][4].type = WalkableWin;
	GenerateModels();
	change = true;
}

void Map::GenerateMap1()
{
	sizeX = 15;
	sizeY = 6;
	spawn = ivec2(0, 1);

	InitTilesMemory();

	for (int x = 0; x < 4; x++)
	{
		for (int y = 1; y < 5; y++)
		{
			tiles[x][y].type = Walkable;
		}
	}

	for (int x = 0; x < 9; x++)
	{
		for (int y = 2; y < 3; y++)
		{
			tiles[x][y].type = Walkable;
		}
	}

	for (int x = 6; x < 9; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			tiles[x][y].type = Walkable;
		}
	}

	for (int x = 6; x < 13; x++)
	{
		for (int y = 0; y < 1; y++)
		{
			tiles[x][y].type = Walkable;
		}
	}

	for (int x = 11; x < 13; x++)
	{
		for (int y = 0; y < 5; y++)
		{
			tiles[x][y].type = Walkable;
		}
	}

	for (int x = 12; x < 15; x++)
	{
		for (int y = 2; y < 6; y++)
		{
			tiles[x][y].type = Walkable;
		}
	}

	tiles[13][3].type = WalkableWin;
	GenerateModels();
	change = true;
}

void Map::GenerateMap2()
{
	sizeX = 15;
	sizeY = 10;
	spawn = ivec2(0, 3);

	InitTilesMemory();

	for (int x = 0; x < 6; x++)
	{
		for (int y = 3; y < 4; y++)
		{
			tiles[x][y].type = Walkable;
		}
	}

	for (int x = 4; x < 6; x++)
	{
		for (int y = 4; y < 6; y++)
		{
			tiles[x][y].type = Walkable;
		}
	}

	for (int x = 6; x < 7; x++)
	{
		for (int y = 4; y < 9; y++)
		{
			tiles[x][y].type = Walkable;
		}
	}

	for (int x = 7; x < 10; x++)
	{
		for (int y = 7; y < 10; y++)
		{
			tiles[x][y].type = Walkable;
		}
	}

	for (int x = 9; x < 11; x++)
	{
		for (int y = 6; y < 9; y++)
		{
			tiles[x][y].type = Walkable;
		}
	}

	for (int x = 5; x < 6; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			tiles[x][y].type = Walkable;
		}
	}

	for (int x = 6; x < 11; x++)
	{
		for (int y = 0; y < 1; y++)
		{
			tiles[x][y].type = Walkable;
		}
	}

	for (int x = 8; x < 11; x++)
	{
		for (int y = 1; y < 3; y++)
		{
			tiles[x][y].type = Walkable;
		}
	}

	for (int x = 11; x < 13; x++)
	{
		for (int y = 2; y < 5; y++)
		{
			tiles[x][y].type = Walkable;
		}
	}

	
	for (int x = 12; x < 15; x++)
	{
		for (int y = 3; y < 6; y++)
		{
			tiles[x][y].type = Walkable;
		}					  
	}
	tiles[13][4].type = WalkableWin;

	GenerateModels();
	change = true;

}

void Map::FreeHandles()
{
	for (int i = 0; i < handles.size(); i++)
		renderer.modelRenders.Remove(handles[i]);

	handles.clear();
}

