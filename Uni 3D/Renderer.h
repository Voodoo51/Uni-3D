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

/*!
	Typ cieniowania (aktualnie dziala tylko BlinnPhong, reszta shaderow pod inne cieniowania nie ma wsparcia pod tekstury).
*/
enum ShadingType
{
	BlinnPhong,
	Gourard,
	Flat
};

using namespace glm;

/*!
	Typ rzutowania.
*/
enum ProjectionType
{
	Perspective,
	Orthographic
};

/*!
		Klasa odpowiedzialna za rysowanie.
*/
class Renderer
{
public:
	/*!
		Funkcja inicjalizujaca.
	*/
	void Init(Camera* camera);
	/*!
		Funkcja odpowiedzialna za rysowanie obiektow.
	*/
	void Draw();
	/*!
		Funkcja ustawiajaca macierz widoku na podstawie przekazanego wektora.
	*/
	void SetView(vec3 playerPos);
	/*!
		Funkcja ustawiajaca macierz widoku na przekazana w argumencie macierz. 
	*/
	void SetView(mat4 view);
	/*!
		Funkcja zmieniajaca rzutowanie.
	*/
	void ChangeProjection();
	/*!
		Funkcja zmieniajaca cieniowanie.
	*/
	void ChangeShading(ShadingType type);

	/*!
			Pozycja swiatla.
	*/
	vec3 lightPos;
	/*!
			Pool zawierajacy wszystkie instancje klasy ModelRender w grze.
	*/
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

/*!
		Instancja renderera.
*/
extern Renderer renderer;