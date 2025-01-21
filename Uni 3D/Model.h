#pragma once
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <vector>
#include "Shader.h"
#include "stb_image.h"

using namespace glm;

/*!
		Struktura reprezentujaca material.
*/
struct Material
{
	Material()
	{
		color = vec3(1.0, 1.0, 1.0);
		float shininess = 32;
	}

	/*!
		Kolor materialu.
	*/
	vec3 color;
	/*!
		Polysk materialu.
	*/
	float shininess;
};

/*!
	Podstawowe prymitywy. Na podstawie danego enuma zmienia sie ulozenie danych ktore trafiaja do bufora wierzcholkow.
*/
enum Primitive
{
	Cube_uv1,
	Cube_uv2
};

/*!
		Klasa reprezentujaca model w grze.
*/
class Model
{
public:
	Model() {};
	Model(Primitive primitive);
	/*!
		Funkcja rysujaca model.
	*/
	void Draw();
	/*!
		Funkcja wczytujaca teksture.
	*/
	void LoadTexture(std::string path);
	/*!
		Lista zawierajaca tekstury modelu.
	*/
	std::vector<unsigned int> textures;

	/*!
		Shader modelu.
	*/
	Shader shader;
	/*!
		VAO modelu.
	*/
	unsigned int VAO;
private:
	void SetVertices(Primitive primitive);
	void SetLayout(Primitive primitive, float* vertices, size_t verticesSize);
};

/*!
		Struktura zawiera dane niezbedne podczas rysowania. Kazdy ModelRender zawiera ID (ktore dziala jako indeks) modelu ktory ma byc rysowany. Instancje ModelRender moga roznic sie pozycja, rotacja, rozmiarem i materialem ale miec przypisane to samo ID modelu. 
*/
struct ModelRender
{
	/*!
		Material.
	*/
	Material material;

	/*!
		ID modelu.
	*/
	int mID;
	/*!
		Pozycja.
	*/
	vec3 pos;
	/*!
		Rotacja.
	*/
	vec3 rot;
	/*!
		Rozmiar.
	*/
	vec3 size;
};