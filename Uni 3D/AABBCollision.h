#pragma once
#include "Transform.h"
#include "DataStructures.h"
#include <glm/glm.hpp>

/*!
	Klasa pozwalająca na wykrywanie i rozwiązywanie kolizji.
*/

using namespace glm;

class AABBCollision
{
public:
	AABBCollision() {};
	//Entity ID 
	//For now it references the sprite ID but I need to change that	
	//unsigned int eID;
	/*!
		Handle do pozycji i rozmiaru collidera.
	*/
	Handle transformHandle;
	/*!
		Funkcja sprawdzająca kolizje miedzy dwoma colliderami.
	*/
	bool IntersectsWith(AABBCollision collider);
	/*!
		Funkcja sprawdzająca kolizje pomiędzy colliderem a wektorem.
	*/
	bool IntersectsWith(vec2 point);
	/*!
		Funkcja zwracająca wektor o który należy przesunąc obiekt aby nie dochodziło do kolizji.
	*/
	vec2 GetMTV(AABBCollision collider);
};

extern Pool<AABBCollision> enemyColliders;