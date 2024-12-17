#include "Renderer.h"

Renderer renderer;

void Renderer::Init(Camera* camera)
{
	this->camera = camera;
	blinnPhongShader.load("basic_vs.txt", "basic_fs.txt");
	gourardShader.load("basic_gourard_vs.txt", "basic_gourard_fs.txt");
	flatShader.load("basic_flat_vs.txt", "basic_flat_fs.txt");
	shader = blinnPhongShader;
	glProvokingVertex(GL_FIRST_VERTEX_CONVENTION);

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

	cli.Init();

	pointLights.push_back(PointLight());
	models.push_back(Model());
	/*
	for (int x = 0; x < 25; x++)
	{
		for (int y = 0; y < 25; y++)
		{
			Handle mrHandle = modelRenders.Append(ModelRender());
			modelRenders.Get(mrHandle).mID = 0;
			modelRenders.Get(mrHandle).pos = vec3(x * 10, 0, y * 10);
			modelRenders.Get(mrHandle).rot = vec3(0, 0, 0);
			modelRenders.Get(mrHandle).size = vec3(10, 10, 10);
			modelRenders.Get(mrHandle).material.diffuse = vec3(0.9, 0.0, 0.0);
			modelRenders.Get(mrHandle).material.specular = vec3(0.0, 0.5, 0.0);
		}
	}
	*/
	/*
	mrHandle = modelRenders.Append(ModelRender());
	modelRenders.Get(mrHandle).mID = 0;
	modelRenders.Get(mrHandle).pos = vec3(2 * 10, 0, 0 * 10);
	modelRenders.Get(mrHandle).rot = vec3(0, 0, 0);
	modelRenders.Get(mrHandle).size = vec3(10, 15, 10);
	modelRenders.Get(mrHandle).material.diffuse = vec3(0.5, 0.5, 0.5);
	modelRenders.Get(mrHandle).material.specular = vec3(0.9, 0.0, 0.0);
	*/
	
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	const char* glslVersion = "#version 410";
	// Setup Platform/Renderer backends
	ImGui_ImplSDL2_InitForOpenGL(window.window, window.context);
	ImGui_ImplOpenGL3_Init(glslVersion);
	
}

void Renderer::Draw()
{
	//glBindVertexArray(VAO);
	glViewport(0, 0, window.SCR_WIDTH, window.SCR_HEIGHT);
	glClearColor(5.0f / 255, 178.0f / 255, 252.0f / 255, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	vec3 center = vec3(24 * 15 / 2.0f, 0, 15 * 24 / 2.0f);

	
	
	/*
	for (int i = 1; i < modelRenders.data.size(); i++)
	{
		modelRenders.data[i].pos.y = 0;
		modelRenders.data[i].pos.y =  20 * sin(distance(modelRenders.data[i].pos, center) / 25 + timer.time / 100);
	}
	*/
	
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

	for (int i = 1; i < modelRenders.data.size(); i++)
	{
		if (!modelRenders.HasIndex(i)) continue;
		glBindVertexArray(models[modelRenders.data[i].mID].VAO);

		shader.use();
		shader.setVec3("dirLight.direction", directionalLight.direction);
		shader.setVec3("dirLight.ambient", directionalLight.ambient);
		shader.setVec3("dirLight.diffuse", directionalLight.diffuse);
		shader.setVec3("dirLight.specular", directionalLight.specular);

		shader.setMat4("projection", projection);
		//view = camera->GetViewMatrix();
		shader.setMat4("view", view);
		mat4 model;
		shader.setInt("pointLightsCount", 1);

		pointLights[0].position = camera->Position;

		model = mat4(1.0);
		model = glm::translate(model, modelRenders.data[i].pos);
		model = glm::rotate(model, modelRenders.data[i].rot.x, vec3(1.0, 0.0, 0.0));
		model = glm::rotate(model, modelRenders.data[i].rot.y, vec3(0.0, 1.0, 0.0));
		model = glm::rotate(model, modelRenders.data[i].rot.z, vec3(0.0, 0.0, 1.0));
		model = glm::scale(model, modelRenders.data[i].size);
		shader.setMat4("model", model);

		shader.setVec3("material.ambient", modelRenders.data[i].material.ambient);
		shader.setVec3("material.diffuse", modelRenders.data[i].material.diffuse);
		shader.setVec3("material.specular", modelRenders.data[i].material.specular);
		shader.setFloat("material.shininess", modelRenders.data[i].material.shininess);

		for (int l = 0; l < pointLights.size(); l++)
		{
			//TODO(): 
			shader.setVec3("pointLights[0].position", pointLights[l].position);
			shader.setFloat("pointLights[0].constant", pointLights[l].constant);
			shader.setFloat("pointLights[0].linear", pointLights[l].linear);
			shader.setFloat("pointLights[0].quadratic", pointLights[l].quadratic);
			shader.setVec3("pointLights[0].ambient", pointLights[l].ambient);
			shader.setVec3("pointLights[0].diffuse", pointLights[l].diffuse);
			shader.setVec3("pointLights[0].specular", pointLights[l].specular);
		}

		models[modelRenders.data[i].mID].Draw();
	}
	
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	io.MousePos = ImVec2(input.mouseXPos, input.mouseYPos);


 // Calling the function of my project at the bottom.

	cli.Draw(io);

	// Create a window
	ImGui::Begin("Renderer");
	ImGui::Text("Tryby cieniowania:");
;	// Add a Button
	if (ImGui::Button("BlinnPhong")) 
		ChangeShading(BlinnPhong);
	if (ImGui::Button("Gourard"))
		ChangeShading(Gourard);
	if (ImGui::Button("Flat"))
		ChangeShading(Flat);

	ImGui::End();



	ImGui::Render();
	glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	/*
	model = translate(model, vec3(0, -2, 5));
	model = scale(model, vec3(20, 20, 20));
	basicShader.setMat4("model", model);
	*/
	//glDrawArrays(GL_TRIANGLES, 0, 36);
	//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void Renderer::SetView(vec3 playerPos)
{
	view = lookAt(playerPos + vec3(4*2, 4*10, 4*5), playerPos, camera->Up);
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

void Renderer::ChangeShading(ShadingType type)
{
	switch (type)
	{
	case BlinnPhong:
		shader = blinnPhongShader;
		break;
	case Gourard:
		shader = gourardShader;
		break;
	case Flat:
		shader = flatShader;
		break;
	}
}