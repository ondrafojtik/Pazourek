#include "PlayGround.h"

static const char* s_grid =
"GGGGGFGGGGGGGGG"
"GGGFFFGGGGGUGGG"
"GGGGFFFGGGGVGGG"
"GGGGGGGGGGGVGGG"
"GGGGGGGGGGGDGGG"
"GGGGGGGGGGGGGGG"
"GGGGGGFFFGGGGGG"
"GGGGGGGGFGGGGGG";

static bool isCollidable(char c)
{
	if ((c == 'F') || (c == 'V'))
		return true;
	return false;
}

void PlayGround::OnAttach()
{
	myParticles->Init();
	textures['G'] = m_SubGrass;
	textures['F'] = m_SubForest;
	textures['D'] = m_SubDown;
	textures['V'] = m_SubVertical;
	textures['U'] = m_SubUp;

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
		cameraY= cameraY + 5;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraX = cameraX - 5;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraY = cameraY - 5;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraX = cameraX + 5;
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		cameraZoom = cameraZoom - 1;
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		cameraZoom = cameraZoom + 1;
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		myParticles->Add((float)cursorX, (float)cursorY, ParticleLife, ParticleStartingColor, ParticleDyingColor, glm::vec2(ParticleSize, ParticleSize));
	
	//setting camera position based on input
	camera->SetPosition(cameraX, cameraY);
	camera->SetZoom(cameraZoom);

	myParticles->Update();
}

void PlayGround::OnRender()
{
	renderer->Clear();

	renderer->DrawQuad(glm::vec4(1.0f), { 0.0f, 0.0f }, {50.0f, 50.0f});

	//rendering map here, its pretty crappy. Theres definitely nicer way of doing this 
	float step = 128.0f;
	for (int y = 0; y < 8; y++)
		for (int x = 0; x < 15; x++)
		{
			char c = s_grid[x + (y * 15)];
			m_SubTex = textures[c];
			renderer->DrawQuad(*m_SubTex, { 128 * x, (-128 * y) });
			
			if (drawGrid)
			{
				if (isCollidable(c)) //bacically "if collidable.." 
					renderer->DrawGrid(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), { 128 * x, (-128 * y) });
				else
					renderer->DrawGrid(glm::vec4(0.1f, 0.05f, 0.1f, 1.0f), { 128 * x, (-128 * y) });
			}
		}

	//render player
	//renderer->DrawQuad(*player, { 128.0f + (float)grid_x * 128.0f, (-(float)grid_y  * 128.0f) });
	renderer->DrawQuad(*player, { 128.0f + 0 * 128.0f, (-3 * 128.0f) });

	//particles
	for (Particle elem : myParticles->buffer)
		renderer->DrawQuad(elem.color, { elem.x, elem.y }, elem.size);
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

	float tileSize = 128.0f;
	grid_x = std::floor((cursorX - tileSize / 2) / tileSize);
	grid_y = std::floor((-cursorY + tileSize / 2) / tileSize);
	ImGui::Text("Grid X: %i, Y: %i", grid_x, grid_y);
}