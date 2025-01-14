#include "Renderer.h"

Renderer renderer;

void Renderer::Init(Camera* camera)
{
	this->camera = camera;
	blinnPhongShader.load("basic_vs.txt", "basic_fs.txt");
	gourardShader.load("basic_gourard_vs.txt", "basic_gourard_fs.txt");
	flatShader.load("basic_flat_vs.txt", "basic_flat_fs.txt");
	postprocessShader.load("postprocess_vs.txt", "postprocess_fs.txt");

	shader = blinnPhongShader;
	glProvokingVertex(GL_FIRST_VERTEX_CONVENTION);
	lightPos = vec3(5, 11, 5);
	renderScale = 1;

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
	InitFrameBuffer();


	cli.Init();

	pointLights.push_back(PointLight());
	//pointLights[0].position = vec3(5, 2, 5);
	models.push_back(Model(Cube_uv1));
	//models[0].LoadTexture("Textures/container2.png");
	//models[0].LoadTexture("Textures/container2_specular.png");
	//Rock013_1K-PNG_Color.png
	//Rock013_1K-PNG_NormalGL.png
	models[0].LoadTexture("Textures/Tiles093_1K-PNG_Color.png");
	models[0].LoadTexture("Textures/blankBlack.png");
	models[0].LoadTexture("Textures/Tiles093_1K-PNG_NormalGL.png");

	models[0].LoadTexture("Textures/Tiles093_1K-PNG_Displacement.png");
	//models[0].LoadTexture("Textures/parallaxTest.png");
	//models[0].LoadTexture("Textures/cobbleTilesRoughness.jpg");
	//models[0].LoadTexture("Textures/cobbleTilesNormal.jpg");
	
	/*
	models[0].LoadTexture("Textures/blank.png");
	//models[0].LoadTexture("Textures/blankBlack.png");
	models[0].LoadTexture("Textures/specularRock.png");
	models[0].LoadTexture("Textures/NormalMapTest.png");
	*/

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

	//consider doing this manually
	glEnable(GL_FRAMEBUFFER_SRGB);

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
	

	glGenTextures(1, &textureTest);
	glBindTexture(GL_TEXTURE_2D, textureTest);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	std::string path = "Textures/test2.jpg";
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}

void Renderer::Draw()
{
	//glBindVertexArray(VAO);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glClearColor(0, 0, 0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, window.SCR_WIDTH / renderScale, window.SCR_HEIGHT / renderScale);
	//glClearColor(5.0f / 255, 178.0f / 255, 252.0f / 255, 1.0f);
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
		shader.setInt("albedo", 0);
		shader.setInt("specular", 1);
		shader.setInt("normalMap", 2);
		shader.setInt("heightMap", 3);
		shader.setFloat("heightScale", -0.1f);

		pointLights[0].position = lightPos;
		//if (Camera::freeFlightOn)
		//{
		//	pointLights[0].position = camera->Position;
		//}

		model = mat4(1.0);
		model = glm::translate(model, modelRenders.data[i].pos);
		model = glm::rotate(model, modelRenders.data[i].rot.x, vec3(1.0, 0.0, 0.0));
		model = glm::rotate(model, modelRenders.data[i].rot.y, vec3(0.0, 1.0, 0.0));
		model = glm::rotate(model, modelRenders.data[i].rot.z, vec3(0.0, 0.0, 1.0));
		model = glm::scale(model, modelRenders.data[i].size);
		shader.setMat4("model", model);
		shader.setVec3("material.color", modelRenders.data[i].material.color);
		shader.setFloat("material.shininess", modelRenders.data[i].material.shininess);

		for (int t = 0; t < models[modelRenders.data[i].mID].textures.size(); t++)
		{
			glActiveTexture(GL_TEXTURE0 + t);
			glBindTexture(GL_TEXTURE_2D, models[modelRenders.data[i].mID].textures[t]);
		}

		//shader.setVec3("material.ambient", modelRenders.data[i].material.ambient);
		//shader.setVec3("material.diffuse", modelRenders.data[i].material.diffuse);
		//shader.setVec3("material.specular", modelRenders.data[i].material.specular);
		shader.setInt("lightPosCount", 1);
		shader.setVec3("viewPos", camera->Position);

		for (int l = 0; l < pointLights.size(); l++)
		{
			//TODO(): 
			shader.setVec3("lightPos", pointLights[l].position);
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

	//cli.Draw(io);

	/*
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
	*/


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
	// second pass
	glBindFramebuffer(GL_FRAMEBUFFER, 0); // back to default
	glViewport(0, 0, window.SCR_WIDTH, window.SCR_HEIGHT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	postprocessShader.use();
	glBindVertexArray(framebufferVAO);
	glDisable(GL_DEPTH_TEST);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, framebufferTexture);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer::SetView(vec3 playerPos)
{
	view = lookAt(playerPos + vec3(4*2, 4*10, 4*5), playerPos, camera->Up);
	camera->Position = playerPos + vec3(4 * 2, 4 * 10, 4 * 5);
}

void Renderer::SetView(mat4 view)
{
	this->view = view;
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

void Renderer::InitFrameBuffer()
{
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glGenTextures(1, &framebufferTexture);
	glBindTexture(GL_TEXTURE_2D, framebufferTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB, window.SCR_WIDTH / renderScale, window.SCR_HEIGHT / renderScale, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	// attach it to currently bound framebuffer object
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, framebufferTexture, 0);

	glGenRenderbuffers(1, &framebufferRBO);
	glBindRenderbuffer(GL_RENDERBUFFER, framebufferRBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, window.SCR_WIDTH / renderScale, window.SCR_HEIGHT / renderScale);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, framebufferRBO);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	float vertices[] = {
		-1.0, -1.0, 0.0, 0.0,
		-1.0,  1.0, 0.0, 1.0,
		 1.0,  1.0, 1.0, 1.0,

		-1.0, -1.0, 0.0, 0.0,
		 1.0, -1.0, 1.0, 0.0,
		 1.0,  1.0, 1.0, 1.0
	};

	unsigned int framebufferVBO;

	glGenVertexArrays(1, &framebufferVAO);
	glGenBuffers(1, &framebufferVBO);
	glBindVertexArray(framebufferVAO);

	glBindBuffer(GL_ARRAY_BUFFER, framebufferVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);
}