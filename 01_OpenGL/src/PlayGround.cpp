#include "PlayGround.h"
/*
static glm::vec2 grid_to_position(const glm::vec2& grid)
{
	glm::vec2 pos = glm::vec2((grid.x * tileSize), -grid.y * tileSize);
	//{ 128.0f + grid.x * 128.0f, (-grid.y * 128.0f) }
	return pos;
}

static glm::vec2 position_to_grid(const glm::vec2& position)
{
	glm::vec2 grid = glm::vec2(
		std::ceilf((position.x - tileSize / 2) / tileSize),
		std::floorf((-position.y + tileSize / 2) / tileSize)
	);
	return grid;
}*/

void PlayGround::OnAttach()
{
	//grid init!
	for (int y = 0; y < 8; y++)
		for (int x = 0; x < 15; x++)
		{
			s_nodeGrid[x + (y * 15)].grid_type = s_grid[x + (y * 15)];
			s_nodeGrid[x + (y * 15)].position = { x, y };
		}

	pathFinder->Init(s_nodeGrid);
	myParticles->Init();
	textures['G'] = m_SubGrass;
	textures['F'] = m_SubForest;
	textures['D'] = m_SubDown;
	textures['V'] = m_SubVertical;
	textures['U'] = m_SubUp;
	
	camera->position.x = 896;
	camera->position.y = -420;
}

void PlayGround::OnDetach()
{
	delete camera;
	delete renderer;
	delete tex;
	delete myParticles;
	delete m_SubDown;
	delete m_SubForest;
	delete m_SubGrass;
	delete m_SubUp;
	delete m_SubVertical;
	delete m_SubTex;
}

void PlayGround::OnUpdate()
{
	//getting cursor position
	glfwGetCursorPos(window, &cursorX, &cursorY);
	cursorX = (cursorX + camera->GetXOffset());
	cursorY = (glm::abs(1080.0f - (float)cursorY) + camera->GetYOffset());
	
	//I should rly make some sort of event system
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->position.y += 2.0f;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->position.x -= 2.0f;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->position.y -= 2.0f;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->position.x += 2.0f;
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		cameraZoom = cameraZoom + 2;
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		cameraZoom = cameraZoom - 2;
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
	{ 
		float windowWidth = 1920.0f;
		float windowHeight = 1080.0f;

		float x = 16 * camera->GetZoom();
		float y = 9 * camera->GetZoom();
		//float posX = (-camera->position.x - 896 + cursorX) + (windowWidth / 2 / x);
		//float posY = cursorY; // + (windowHeight / 2 / y);
		myParticles->Add(cursorX, cursorY, ParticleLife, ParticleStartingColor, ParticleDyingColor, glm::vec2(ParticleSize, ParticleSize));
		
	}
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
	{
		pathFinder->Solve(s_nodeGrid, &s_nodeGrid[4], &s_nodeGrid[grid_to_i(grid)]);
		node_to_render_from = s_nodeGrid[grid_to_i(grid)];
		render_path = 1;
	}
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
		render_path = 0;
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
		camera->rotation += 0.01f;


	//setting camera position based on input
	camera->SetPosition(cameraX, cameraY);
	camera->SetZoom(cameraZoom);

	myParticles->Update();
}

void PlayGround::OnRender()
{
	renderer->Clear();

	//rendering map
	for (auto node : s_nodeGrid)
	{
		m_SubTex = textures[node.grid_type];
		renderer->DrawQuad(*m_SubTex, { tileSize * node.position.x, -tileSize * node.position.y });
		if (drawGrid)
		{
			if (node.collidable) //bacically "if collidable.." 
				renderer->DrawGrid(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), grid_to_position(node.position));
			else
				renderer->DrawGrid(glm::vec4(0.1f, 0.05f, 0.1f, 1.0f), grid_to_position(node.position));
		}
	}

	//render player
	//renderer->DrawQuad(*player, grid_to_position(grid));
	int x = 4;
	int y = 0;
	renderer->DrawQuad(*player, grid_to_position(s_nodeGrid[grid_to_i({ x, y })].position));
	//renderer->DrawGrid(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), grid_to_position(s_nodeGrid[x + (y * 15)].position));
	//renderer->DrawGrid(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), grid_to_position(s_nodeGrid[(x + 1) + (y * 15)].position));
	//renderer->DrawGrid(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), grid_to_position(s_nodeGrid[(x - 1) + (y * 15)].position));
	//renderer->DrawGrid(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), grid_to_position(s_nodeGrid[x + ((y + 1) * 15)].position));
	//renderer->DrawGrid(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), grid_to_position(s_nodeGrid[x + ((y - 1) * 15)].position));

	//particles
	for (Particle elem : myParticles->buffer)
		renderer->DrawQuad(elem.color, { elem.x, elem.y }, elem.size);

	if(render_path)
	{
		//Node node = s_nodeGrid[6];
		Node node = node_to_render_from;
		while (node.parent != nullptr)
		{
			renderer->DrawGrid(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), grid_to_position(node.position));
			node = *node.parent;
		}
		renderer->DrawGrid(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), grid_to_position({x, y}));
	}
}

void PlayGround::ImGuiOnUpdate()
{
	ImGui::SliderFloat("ParticleSize", &ParticleSize, 0, 200);
	ImGui::SliderFloat("ParticleLife", &ParticleLife, 0, 500);
	ImGui::ColorEdit4("StartingColor", glm::value_ptr(ParticleStartingColor));
	ImGui::ColorEdit4("DyingColor", glm::value_ptr(ParticleDyingColor));
	ImGui::Text("particleBufferSize: %f", (float)myParticles->buffer.size());
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::Text("Cursor X: %f, Y: %f", (float)cursorX, (float)cursorY);
	ImGui::Checkbox("Grid: ", &drawGrid);
	ImGui::SameLine();
	if (ImGui::Button("Reset camera", { 100, 20 }))
	{
		camera->position.x = -896;
		camera->position.y = 420;
		camera->rotation = 0.0f;
		cameraZoom = 60;
		//cameraX = -64.0f;
		//cameraY = 64.0f - 1026;
		//cameraZoom = 1.0f;
		std::cout << "camera reset!\n";
	}

	grid = position_to_grid(glm::vec2(cursorX, cursorY));
	if (ImGui::Button("Terminate", { 100, 20 }))
	{
		glfwTerminate();
	}
	//grid.x = std::ceilf((cursorX - tileSize / 2) / tileSize);
	//grid.y = std::floorf((-cursorY + tileSize / 2) / tileSize);
	ImGui::Text("Grid X: %i, Y: %i, Final: %i", (int)grid.x, (int)grid.y, (int)(grid.x + (grid.y * 15)));
	ImGui::Text("CameraZoom: %f", camera->GetZoom());
	ImGui::Text("Camera position: %f, %f", camera->position.x, camera->position.y);
}