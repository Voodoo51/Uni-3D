#pragma once
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <vector>
#include "Shader.h"
#include "stb_image.h"

using namespace glm;

struct Material
{
	Material()
	{
		color = vec3(1.0, 1.0, 1.0);
		float shininess = 32;
	}

	vec3 color;
	float shininess;
};

enum Primitive
{
	Cube_uv1,
	Cube_uv2
};

class Model
{
public:
	Model() {};
	Model(Primitive primitive);
	void Draw();
	void LoadTexture(std::string path);
	std::vector<unsigned int> textures;

	Shader shader;
	unsigned int VAO;
private:
	void SetVertices(Primitive primitive);
	void SetLayout(Primitive primitive, float* vertices, size_t verticesSize);
};

struct ModelRender
{
	Material material;

	int mID;
	vec3 pos;
	vec3 rot;
	vec3 size;
};