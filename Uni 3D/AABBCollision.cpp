#include "AABBCollision.h"

Pool<AABBCollision> enemyColliders;

bool AABBCollision::IntersectsWith(AABBCollision collider)
{
	vec2 ourPos = transforms.Get(transformHandle).position;//renderer.sprites[eID].position;
	vec2 ourSize = transforms.Get(transformHandle).size;//renderer.sprites[eID].size;

	vec2 colliderPos = transforms.Get(collider.transformHandle).position;
	vec2 colliderSize = transforms.Get(collider.transformHandle).size;

	if (ourPos.x > (colliderPos.x + colliderSize.x)) return false;
	if ((ourPos.x + ourSize.x) <  colliderPos.x) return false;
	if (ourPos.y > (colliderPos.y + colliderSize.y)) return false;
	if ((ourPos.y + ourSize.y) < colliderPos.y) return false;

	return true;
}

bool AABBCollision::IntersectsWith(vec2 point)
{
	vec2 ourPos = transforms.Get(transformHandle).position;//renderer.sprites[eID].position;
	vec2 ourSize = transforms.Get(transformHandle).size;//renderer.sprites[eID].size;

	if (point.x < ourPos.x) return false;
	if (point.x > ourPos.x + ourSize.x) return false;
	if (point.y < ourPos.y) return false;
	if (point.y > ourPos.y + ourSize.y) return false;

	return true;
}

//https://dyn4j.org/2010/01/sat/
//MTV = Minimum Translation Vector
//This is "optimizable". We only need to calculate two dot products for each axis for each box
vec2 AABBCollision::GetMTV(AABBCollision collider)
{
	vec2 ourPos = transforms.Get(transformHandle).position;//renderer.sprites[eID].position;
	vec2 ourSize = transforms.Get(transformHandle).size;//renderer.sprites[eID].size;

	vec2 colliderPos = transforms.Get(collider.transformHandle).position;
	vec2 colliderSize = transforms.Get(collider.transformHandle).size;

	vec2 axis[2] = { vec2(0,1), vec2(1, 0) };

	vec2 ourVertices[4] = {	 ourPos, 
						vec2(ourPos.x + ourSize.x, ourPos.y), 
						vec2(ourPos.x, ourPos.y + ourSize.y), 
						vec2(ourPos.x + ourSize.x, ourPos.y + ourSize.y)};

	vec2 colliderVertices[4] = { colliderPos,
							vec2(colliderPos.x + colliderSize.x, colliderPos.y), 
							vec2(colliderPos.x, colliderPos.y + colliderSize.y), 
							vec2(colliderPos.x + colliderSize.x, colliderPos.y + colliderSize.y) };



	float overlap = 9999;
	vec2 smallestAxis;
	int flip = 1;

	for (int a = 0; a < 2; a++)
	{
		float ourMin = 99999;
		float ourMax = -99999;

		float colliderMin = 99999;
		float colliderMax = -99999;

		for (int i = 0; i < 4; i++)
		{
			float ourDot = dot(axis[a], ourVertices[i]);
			float colliderDot = dot(axis[a], colliderVertices[i]);

			if (ourDot < ourMin)
			{
				ourMin = ourDot;
			}
			else if (ourDot > ourMax)
			{
				ourMax = ourDot;
			}

			if (colliderDot < colliderMin)
			{
				colliderMin = colliderDot;
			}
			else if (colliderDot > colliderMax)
			{
				colliderMax = colliderDot;
			}
		}
		
		float o = min(ourMax, colliderMax) - max(ourMin, colliderMin);

		if (o < overlap)
		{
			if (ourMin < colliderMin)
			{
				flip = 1;
			}
			else
			{
				flip = -1;
			}

			overlap = o;
			smallestAxis = axis[a];
		}
		
	}
	overlap *= flip;
	return smallestAxis * overlap;
}