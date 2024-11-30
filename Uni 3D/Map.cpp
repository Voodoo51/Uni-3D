#include "Map.h"

Tile::Tile(TileType type)
{
	this->type = type;
}

void Map::Init()
{
	srand(time(NULL));
	
	for (int x = 0; x < 20; x++)
	{
		for (int y = 0; y < 20; y++)
		{
			int randomValue = rand() % 6;

			if (randomValue < 3)
				tiles[x][y].type = Walkable;
			else
				tiles[x][y].type = NonWalkable;
		}
	}

	for (int x = 0; x < 20; x++)
	{
		for (int y = 0; y < 20; y++)
		{
			if (tiles[x][y].type == Walkable)
			{
				Handle handle = renderer.modelRenders.Append(ModelRender());
				renderer.modelRenders.Get(handle).pos = vec3(x * 10, 0, y * 10);
				renderer.modelRenders.Get(handle).size = vec3(10, 10, 10);
			}
		}
	}

}

