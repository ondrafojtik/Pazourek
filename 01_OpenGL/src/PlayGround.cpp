#include "PlayGround.h"

void PlayGround::OnAttach()
{
	//grid init!
	map->Save(s_grid);
	map->Reload();
	s_grid = map->s_grid;

	for (int y = 0; y < 800; y++)
		for (int x = 0; x < 800; x++)
		{
			s_nodeGrid[x + (y * 800)].grid_type = s_grid[1];
			s_nodeGrid[x + (y * 800)].position = { x, y };
		}

	//pathFinder->Init(s_nodeGrid);
	myParticles->Init();
	textures['G'] = m_SubGrass;
	textures['F'] = m_SubForest;
	textures['D'] = m_SubDown;
	textures['V'] = m_SubVertical;
	textures['U'] = m_SubUp;
	textures['I'] = m_SubIce;
	textures['T'] = m_SubTree;

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
	glfwGetCursorPos(window, &mouse_position->x, &mouse_position->y);

	//I should rly make some sort of event system
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraY += 8.0f;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraX -= 8.0f;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraY -= 8.0f;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraX += 8.0f;
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		cameraZoom = cameraZoom + 2;
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		cameraZoom = cameraZoom - 2;
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
	{
		float x = mouse_position->x;
		float y = mouse_position->y;

		float windowWidth = 1920.0f;
		float windowHeight = 1080.0f;

		cameraBounds bounds = camera->bounds;
		auto pos = camera->position;
		x = (x / windowWidth) * bounds.getWidth() - bounds.getWidth() * 0.5f;
		y = bounds.getHeight() * 0.5f - (y / windowHeight) * bounds.getHeight();
		x = x + pos.x;
		y = y + pos.y;

		myParticles->Add(x, y, ParticleLife, ParticleStartingColor, ParticleDyingColor, glm::vec2(ParticleSize, ParticleSize));
		myParticles->Add(x, y, ParticleLife, ParticleStartingColor, ParticleDyingColor, glm::vec2(ParticleSize, ParticleSize));
		myParticles->Add(x, y, ParticleLife, ParticleStartingColor, ParticleDyingColor, glm::vec2(ParticleSize, ParticleSize));

	}
	
	//setting camera position based on input
	camera->SetPosition(cameraX, cameraY);
	camera->SetZoom(cameraZoom);

	myParticles->Update();

	grid = position_to_grid(glm::vec2(mouse_position->x, mouse_position->GetYInverse()));

	m_Animation->OnUpdate();
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

	//particles
	for (Particle elem : myParticles->buffer)
		renderer->DrawQuad(elem.color, { elem.x, elem.y }, elem.size, 0.0f);


	//rendering anim.
	renderer->DrawQuad(*m_Animation->currentAnimation, { 768, -128 });

	renderer->DrawQuad(*tex_alonso, { -500, -500 });
	
}

void PlayGround::ImGuiOnUpdate()
{
	ImGui::Begin("Debug");
	ImGui::Text("Cursor X: %f, Y: %f", (float)mouse_position->x, (float)mouse_position->GetYInverse());
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

		std::cout << "camera reset!\n";
	}

	//ImGui::Text("Grid X: %i, Y: %i, Final: %i", (int)grid.x, (int)grid.y, (int)(grid.x + (grid.y * 15)));
	ImGui::Text("CameraZoom: %f", camera->GetZoom());
	ImGui::Text("Camera position: %f, %f", camera->position.x, camera->position.y);
	ImGui::End();


}
