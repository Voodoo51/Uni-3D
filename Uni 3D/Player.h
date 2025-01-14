#pragma once
#include "Input.h"
#include "Map.h"
#include <cmath>
#include <glm/gtx/rotate_vector.hpp>

class Map;
class Tile;
enum TileType;

enum LayingState
{
	Upwards,
	DownSideways,  
	DownUp
};

class Player
{
public:
	void Init();
	void SetMap(Map map);
	void Update();
	Handle model;
private:
	float Lerp(float a, float b, float t);
	void Move(int moveX, int moveY);
	bool CanMove(int x, int y);
	std::vector<ivec2> containtedTiles;
	LayingState layingState;
	LayingState afterMoveState;
	bool animating;
	float t;
	vec3 targetRot;
	vec3 prevRot;
	vec2 pos;
	vec2 prevPos;
	int lastMoveX;
	int lastMoveY;
	Map currentMap;
	bool skipFrame;
};

extern Player player;
