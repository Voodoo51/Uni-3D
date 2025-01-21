#pragma once
#include "Input.h"
#include "GameManager.h"
#include <cmath>
#include <glm/gtx/rotate_vector.hpp>

class Map;
class Tile;
enum TileType;

/*!
	Stany ulozenia gracza.
*/
enum LayingState
{
	Upwards,
	DownSideways,  
	DownUp
};

/*!
	Klasa reprezentujaca gracza.
*/
class Player
{
public:
	/*!
		Funkcja inicjalizujaca.
	*/
	void Init();
	/*!
		Funkcja ustawiajaca mape gracza i resetujaca jego stan.
	*/
	void SetMap(Map map);
	/*!
		Funkcja wykonywujaca logike gracza.
	*/
	void Update();
	/*!
		Handle na ModelRender gracza.
	*/
	Handle model;
private:
	float Lerp(float a, float b, float t);
	void Move(int moveX, int moveY);
	bool CanMove(int x, int y);
	bool CanWin(int x, int y);
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

	bool won;
	bool expectedWin;
};

extern Player player;
