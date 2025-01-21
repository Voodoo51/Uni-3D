#pragma once
#include "Math.h"
#include "DataStructures.h"
#include <glm/glm.hpp>

using namespace glm;
/*!
	Struktura zawierająca informacje o pozycji, rozmiarze i kącie (w 2D).
*/
struct Transform
{
	vec2 position;
	vec2 size;
	float angle = 0;
};

/*!
	Pool wszystkich instancji klasy Transform w grze.
*/
extern Pool<Transform> transforms;