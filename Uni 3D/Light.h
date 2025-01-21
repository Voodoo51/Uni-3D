#pragma once
#include "glm/glm.hpp"

using namespace glm;

/*!
	Struktura reprezentujaca swiatlo kierunkowe (np. slonce).
*/
struct DirectionalLight
{
	DirectionalLight()
	{
		direction = vec3(0.0, -1.0, 1.0);
		direction = normalize(direction);

		ambient = vec3(0.0, 0.0, 0.0);
		diffuse = vec3(0.1, 0.1, 0.1);
		specular = vec3(0.1, 0.1, 0.1);
	}

	/*!
		Kierunek swiatla.
	*/
	vec3 direction;
	/*!
		Kolor komponentu ambient.
	*/
	vec3 ambient;
	/*!
		Kolor komponentu diffuse.
	*/
	vec3 diffuse;
	/*!
		Kolor komponentu specular.
	*/
	vec3 specular;
};

/*!
		Instancja swiatla kierunkowego (silnik ma wsparcie tylko pod jedna instancje tego typu swiatla).
*/
extern DirectionalLight directionalLight;

/*!
		Struktura swiatla punktowego.
*/
struct PointLight
{
	PointLight()
	{
		position = vec3(0.0, 0.0, 0.0);

		constant = 1.0f;
		linear = 0.09f;
		quadratic = 0.032f;

		ambient = vec3(0.2, 0.2, 0.2);
		diffuse = vec3(1.0, 1.0, 1.0);
		specular = vec3(0.5, 0.5, 0.5);
	}

	/*!
		Pozycja swiatla.
	*/
	vec3 position;

	/*!
		Zmienna constant wplywajaca stale na tlumienie swiatla.
		https://learnopengl.com/Lighting/Light-casters
	*/
	float constant;
	/*!
		Zmienna linear wplywajaca liniowo na tlumienie swiatla.
		https://learnopengl.com/Lighting/Light-casters
	*/
	float linear;
	/*!
		Zmienna quadratic wplywajaca kwadratowo na tlumienie swiatla.
		https://learnopengl.com/Lighting/Light-casters
	*/
	float quadratic;

	/*!
		Kolor komponentu ambient.
	*/
	vec3 ambient;
	/*!
		Kolor komponentu diffuse.
	*/
	vec3 diffuse;
	/*!
		Kolor komponentu specular.
	*/
	vec3 specular;
};