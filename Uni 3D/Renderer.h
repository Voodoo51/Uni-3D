#pragma once
#include "Shader.h"
#include "Camera.h"
#include "Window.h"
#include "Model.h"
#include "DataStructures.h"
#include "Light.h"
#include <glm/glm.hpp>
#include "Timer.h"
#include "CLI.h"
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl2.h"

enum ShadingType
{
	BlinnPhong,
	Gourard,
	Flat
};

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
	void ChangeShading(ShadingType type);

	Pool<ModelRender> modelRenders;
private:

	Camera* camera;
	Shader shader;
	Shader blinnPhongShader;
	Shader gourardShader;
	Shader flatShader;
	mat4 projection;
	mat4 perspective;
	mat4 view;
	mat4 orthographic;
	ProjectionType projectionType;

	std::vector<PointLight> pointLights;
	std::vector<Model> models;

	//DO WYJEBANIA
	bool show_demo_window = true;
	bool show_another_window = false;

	mat4 model;
	unsigned int VAO;
	unsigned int VBO;
	unsigned int NBO;
	unsigned int EBO;
};

extern Renderer renderer;