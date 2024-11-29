#pragma once
#include <glm/glm.hpp>
#include <glad/glad.h>

using namespace glm;

struct Material
{
	Material()
	{
		ambient = vec3(0.2, 0.2, 0.2);
		diffuse = vec3(0.5, 0.5, 0.5);
		specular = vec3(0.7, 0.7, 0.7);
		float shininess = 0.5f;
	}

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

class Model
{
public:
	Model();
	void Draw();

	unsigned int VAO;
};

struct ModelRender
{
	Material material;

	int mID;
	vec3 pos;
	vec3 rot;
	vec3 size;
};