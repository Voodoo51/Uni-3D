#pragma once
#include <cstdlib>
#include <ctime>
#include "Renderer.h"

/*!
	Typy kostki.
*/
enum TileType
{
	Walkable,
	NonWalkable,
	WalkableWin
};

/*!
	Klasa reprezentujaca kostke na mapie.
*/
class Tile
{
public:
	Tile() {};
	Tile(TileType type);
	/*!
		Typ kostki.
	*/
	TileType type;
};

/*!
	Klasa reprezentujaca mape.
*/
class Map
{
public:
	/*!
		DEPRECATED
	*/
	void Init();
	/*!
		Funkcja generujaca mape o podanym rozmiarze. 
	*/
	void GenerateMap(int sizeX, int sizeY);
	/*!
		Funkcja generujaca pierwszy poziom.
	*/
	void GenerateMap0();
	/*!
		Funkcja generujaca drugi poziom.
	*/
	void GenerateMap1();
	/*!
		Funkcja generujaca trzeci poziom.
	*/
	void GenerateMap2();
	/*!
		Funkcja zwalniajaca liste handle's do modelow kostek na mapie.
	*/
	void FreeHandles();

	/*!
		Podwojny wskaznik zawierajacy wszystkie kostki na mapie.
	*/
	Tile** tiles;
	/*!
		Pozycja pierwotna na danej mapie.
	*/
	ivec2 spawn;
	/*!
		Rozmiar mapy na osi X.
	*/
	int sizeX;
	/*!
		Rozmiar mapy na osi Y.
	*/
	int sizeY;
	/*!
		Zmienna informujaca gracza o zmianie mapy.
	*/
	bool change;
private:
	void GenerateModels();
	void InitTilesMemory();
	std::vector<Handle> handles;
};

//extern Map map;