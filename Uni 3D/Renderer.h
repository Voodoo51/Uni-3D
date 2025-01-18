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
#include "FadeInOut.h"

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
	void SetView(mat4 view);
	void ChangeProjection();
	void ChangeShading(ShadingType type);

	//only for testing
	vec3 lightPos;
	Pool<ModelRender> modelRenders;
private:
	friend class FadeInOut;
	void InitFrameBuffer();
	Camera* camera;
	Shader shader;
	Shader blinnPhongShader;
	Shader gourardShader;
	Shader flatShader;
	Shader postprocessShader;
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
	unsigned int textureTest;
	mat4 model;
	int renderScale;
	unsigned int framebuffer;
	unsigned int framebufferTexture;
	unsigned int framebufferRBO;
	unsigned int framebufferVAO;
	unsigned int VAO;
	unsigned int VBO;
	unsigned int NBO;
	unsigned int EBO;
};

extern Renderer renderer;