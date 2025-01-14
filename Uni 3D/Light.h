#pragma once
#include "glm/glm.hpp"

using namespace glm;

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
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

extern DirectionalLight directionalLight;

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

	vec3 position;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};