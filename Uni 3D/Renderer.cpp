#include "Renderer.h"

Renderer renderer;

void Renderer::Init(Camera* camera)
{
	this->camera = camera;
	basicShader.load("basic_vs.txt", "basic_fs.txt");

	float aspectRatio = (float)window.SCR_WIDTH / (float)window.SCR_HEIGHT;
	perspective = glm::perspective(glm::radians(camera->Zoom), aspectRatio, 0.1f, 10000.0f);

	float left = -camera->OrthographicSize * aspectRatio;
	float right = camera->OrthographicSize * aspectRatio;
	float bottom = -camera->OrthographicSize;
	float top = camera->OrthographicSize;
	float zNear = 0.1f, zFar = 10000.0f;
	orthographic = glm::ortho(left, right, bottom, top, 0.0f, 10000.0f);
	projection = perspective;
	projectionType = Perspective;

	pointLights.push_back(PointLight());
	models.push_back(Model());


	for (int x = 0; x < 25; x++)
	{
		for (int y = 0; y < 25; y++)
		{
			Handle mrHandle = modelRenders.Append(ModelRender());
			modelRenders.Get(mrHandle).mID = 0;
			modelRenders.Get(mrHandle).pos = vec3(x * 15, 0, y * 15);
			modelRenders.Get(mrHandle).rot = vec3(0, 0, 0);
			modelRenders.Get(mrHandle).size = vec3(10, 10, 10);
		}
	}

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	float vertices[] = {
	   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};
	// fir

	// CENTERED
	/*
	float vertices[] = { -0.5, -0.5, 0.0, 0.0,
						 -0.5,  0.5, 0.0, 1.0,
						  0.5,  0.5, 1.0, 1.0,
						  0.5, -0.5, 1.0, 0.0 };
	*/

	unsigned int indices[] = {
		0, 1, 2, 2, 3, 0, // bottom
		4, 5, 6, 6, 7, 4, // top
		0, 4, 7, 7, 3, 0, // back face
		3, 7, 6, 6, 2, 3, // right face
		1, 5, 4, 4, 0, 1, // left face
		6, 5, 1, 1, 2, 6 // forward face
	};

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

void Renderer::Draw()
{
	//glBindVertexArray(VAO);

	glClearColor(5.0f / 255, 178.0f / 255, 252.0f / 255, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	vec3 center = vec3(24 * 15 / 2.0f, 0, 15 * 24 / 2.0f);

	for (int i = 1; i < modelRenders.data.size(); i++)
	{
		modelRenders.data[i].pos.y = 0;
		modelRenders.data[i].pos.y =  20 * sin(distance(modelRenders.data[i].pos, center) / 25 + timer.time / 100);
	}
		
	for (int i = 1; i < modelRenders.data.size(); i++)
	{
		glBindVertexArray(models[modelRenders.data[i].mID].VAO);

		basicShader.use();
		basicShader.setVec3("dirLight.direction", directionalLight.direction);
		basicShader.setVec3("dirLight.ambient", directionalLight.ambient);
		basicShader.setVec3("dirLight.diffuse", directionalLight.diffuse);
		basicShader.setVec3("dirLight.specular", directionalLight.specular);

		basicShader.setMat4("projection", projection);
		mat4 view = camera->GetViewMatrix();
		basicShader.setMat4("view", view);
		mat4 model;
		basicShader.setInt("pointLightsCount", 1);

		pointLights[0].position = camera->Position;

		model = mat4(1.0);
		model = glm::translate(model, modelRenders.data[i].pos);
		model = glm::rotate(model, modelRenders.data[i].rot.x, vec3(1.0, 0.0, 0.0));
		model = glm::rotate(model, modelRenders.data[i].rot.y, vec3(0.0, 1.0, 0.0));
		model = glm::rotate(model, modelRenders.data[i].rot.z, vec3(0.0, 0.0, 1.0));
		model = glm::scale(model, modelRenders.data[i].size);
		basicShader.setMat4("model", model);

		basicShader.setVec3("material.ambient", modelRenders.data[i].material.ambient);
		basicShader.setVec3("material.diffuse", modelRenders.data[i].material.diffuse);
		basicShader.setVec3("material.specular", modelRenders.data[i].material.specular);
		basicShader.setFloat("material.shininess", modelRenders.data[i].material.shininess);

		for (int l = 0; l < pointLights.size(); l++)
		{
			//TODO(): 
			basicShader.setVec3("pointLights[0].position", pointLights[l].position);
			basicShader.setFloat("pointLights[0].constant", pointLights[l].constant);
			basicShader.setFloat("pointLights[0].linear", pointLights[l].linear);
			basicShader.setFloat("pointLights[0].quadratic", pointLights[l].quadratic);
			basicShader.setVec3("pointLights[0].ambient", pointLights[l].ambient);
			basicShader.setVec3("pointLights[0].diffuse", pointLights[l].diffuse);
			basicShader.setVec3("pointLights[0].specular", pointLights[l].specular);
		}

		models[modelRenders.data[i].mID].Draw();
	}

	/*
	model = translate(model, vec3(0, -2, 5));
	model = scale(model, vec3(20, 20, 20));
	basicShader.setMat4("model", model);
	*/
	//glDrawArrays(GL_TRIANGLES, 0, 36);
	//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void Renderer::ChangeProjection()
{
	if (projectionType == Perspective)
	{
		projection = orthographic;
		projectionType = Orthographic;
	}
	else if(projectionType == Orthographic)
	{
		projection = perspective;
		projectionType = Perspective;
	}
}