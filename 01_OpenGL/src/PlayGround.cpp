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
	textures['I'] = m_SubIce;

	cameraX = 896;
	cameraY = -420;
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
		cameraY += 2.0f;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraX -= 2.0f;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraY -= 2.0f;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraX += 2.0f;
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		cameraZoom = cameraZoom + 2;
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		cameraZoom = cameraZoom - 2;
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
	{
		float windowWidth = 1920.0f;
		float windowHeight = 1080.0f;

		float xPos = cursorX + cameraX - windowWidth / 2;
		float yPos = cursorY + cameraY - windowHeight / 2;
		//float posX = (-camera->position.x - 896 + cursorX) + (windowWidth / 2 / x);
		//float posY = cursorY; // + (windowHeight / 2 / y);
		myParticles->Add(xPos, yPos, ParticleLife, ParticleStartingColor, ParticleDyingColor, glm::vec2(ParticleSize, ParticleSize));

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
		camera->rotation += 0.1f;


	//setting camera position based on input
	camera->SetPosition(cameraX, cameraY);
	camera->SetZoom(cameraZoom);

	myParticles->Update();

	grid = position_to_grid(glm::vec2(cursorX, cursorY));
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

	if (render_path)
	{
		//Node node = s_nodeGrid[6];
		Node node = node_to_render_from;
		while (node.parent != nullptr)
		{
			renderer->DrawGrid(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), grid_to_position(node.position));
			node = *node.parent;
		}
		renderer->DrawGrid(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), grid_to_position({ x, y }));
	}

	//BEGINNING OF EDIT MODE!!!_________________________________________________________________________________________
	if (editMode)
	{
		renderer->DrawQuad(*m_TextureEditMode, grid_to_position(grid));

	}



	//particles
	for (Particle elem : myParticles->buffer)
		renderer->DrawQuad(elem.color, { elem.x, elem.y }, elem.size, 0.0f);

}

void PlayGround::ImGuiOnUpdate()
{
	ImGui::Begin("Debug");
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
		cameraX = 896;
		cameraY = -420;
		camera->rotation = 0.0f;
		cameraZoom = 60;
		camera->SetZoom(cameraZoom);
		camera->SetPosition(cameraX, cameraY);
		//cameraX = -64.0f;
		//cameraY = 64.0f - 1026;
		//cameraZoom = 1.0f;
		std::cout << "camera reset!\n";
	}


	if (ImGui::Button("Terminate", { 100, 20 }))
	{
		glfwTerminate();
	}
	//grid.x = std::ceilf((cursorX - tileSize / 2) / tileSize);
	//grid.y = std::floorf((-cursorY + tileSize / 2) / tileSize);
	ImGui::Text("Grid X: %i, Y: %i, Final: %i", (int)grid.x, (int)grid.y, (int)(grid.x + (grid.y * 15)));
	ImGui::Text("CameraZoom: %f", camera->GetZoom());
	ImGui::Text("Camera position: %f, %f", camera->position.x, camera->position.y);
	ImGui::End();

	ImGui::Begin("Level Editor");


	//theres a need of use "PushID and PopID" since ImGui doesnt like 2widgets or w/e with same "identity". 
	//This goes to ID conflict and it seems like it thinks theres only 1widget (even tho it might render more)
	int iter = 0;
	for (std::pair<char, SubTexture*> sub : textures)
	{
		ImGui::PushID(iter);
		ImGui::SameLine();
		sub.second->m_texture->Bind();
		ImTextureID id = (ImTextureID)sub.second->m_texture->GetTexID();
		
		float left = sub.second->texCoords[0].x;
		float right = sub.second->texCoords[1].x;
		float bottom = sub.second->texCoords[0].y;
		float top = sub.second->texCoords[3].y;

		//ImGui::Image(id, ImVec2(512, 512), { right, top }, { left, bottom });

		if (ImGui::ImageButton(id, { 64, 64 }, { right, top }, { left, bottom }))
		{
			m_TextureEditMode = sub.second;
		}
		ImGui::PopID();
		iter += 1;
	}

	m_TextureEditMode->m_texture->Bind();
	ImTextureID id = (ImTextureID)m_TextureEditMode->m_texture->GetTexID();
	float left = m_TextureEditMode->texCoords[0].x;
	float right = m_TextureEditMode->texCoords[1].x;
	float bottom = m_TextureEditMode->texCoords[0].y;
	float top = m_TextureEditMode->texCoords[3].y;
	ImGui::Text("Currently bound");
	ImGui::Text("x: %f, y: %f", m_TextureEditMode->texCoords[0].x, m_TextureEditMode->texCoords[0].y);
	ImGui::SameLine();
	ImGui::Image(id, ImVec2(128, 128), { right, top }, { left, bottom });

	ImGui::Checkbox("Edit mode", &editMode);
	

	ImGui::End();

}