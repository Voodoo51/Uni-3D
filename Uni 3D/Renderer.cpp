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
		glBindVertexArray(models[modelRenders.data[i].mID].VAO);

		basicShader.use();
		basicShader.setVec3("dirLight.direction", directionalLight.direction);
		basicShader.setVec3("dirLight.ambient", directionalLight.ambient);
		basicShader.setVec3("dirLight.diffuse", directionalLight.diffuse);
		basicShader.setVec3("dirLight.specular", directionalLight.specular);

		basicShader.setMat4("projection", projection);
		//view = camera->GetViewMatrix();
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
	
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	io.MousePos = ImVec2(input.mouseXPos, input.mouseYPos);


 // Calling the function of my project at the bottom.

	cli.Draw(io);

	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);
	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
	{
		static float f = 0.0f;
		static int counter = 0;
		
		ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
		char text[120];
		ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
		ImGui::InputText("test: ", text, IM_ARRAYSIZE(text));               // Display some text (you can use a format strings too)
		ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
		ImGui::Checkbox("Another Window", &show_another_window);

		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		//ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

		if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
		ImGui::End();
		
	}
	// 3. Show another simple window.
	if (show_another_window)
	{
		
		ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::Text("Hello from another window!");
		if (ImGui::Button("Close Me"))
			show_another_window = false;
		ImGui::End();
		
	}


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