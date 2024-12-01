#pragma once
#include "Shader.h"
#include "Camera.h"
#include "Window.h"
#include "Model.h"
#include "DataStructures.h"
#include "Light.h"
#include <glm/glm.hpp>
#include "Timer.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

using namespace glm;

enum ProjectionType
{
	Perspective,
	Orthographic
};

class Renderer
{
public:
	void Init(Camera* camera);
	void Draw();
	void SetView(vec3 playerPos);
	void ChangeProjection();

	Pool<ModelRender> modelRenders;
private:
	Camera* camera;
	Shader basicShader;
	mat4 projection;
	mat4 perspective;
	mat4 view;
	mat4 orthographic;
	ProjectionType projectionType;

	std::vector<PointLight> pointLights;
	std::vector<Model> models;

	mat4 model;
	unsigned int VAO;
	unsigned int VBO;
	unsigned int NBO;
	unsigned int EBO;
};

extern Renderer renderer;