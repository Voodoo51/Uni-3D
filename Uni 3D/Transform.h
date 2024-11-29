#pragma once
#include "Math.h"
#include "DataStructures.h"
#include <glm/glm.hpp>

using namespace glm;
/*!
	Struktura zawierająca informacje o pozycji, rozmiarze i kącie.
*/
struct Transform
{
	vec2 position;
	vec2 size;
	float angle = 0;
};

extern Pool<Transform> transforms;