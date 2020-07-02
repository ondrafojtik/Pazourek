#include "PlayGround.h"

void PlayGround::OnAttach()
{
	myParticles->Init();

}

void PlayGround::OnDetach()
{
	delete camera;
	delete renderer;
	delete tex;
	delete subTex;
	delete myParticles;
}

void PlayGround::OnUpdate()
{
	//getting cursor position
	glfwGetCursorPos(window, &cursorX, &cursorY);
	cursorX = (cursorX + camera->GetXOffset());
	cursorY = (glm::abs(1080 - (float)cursorY) + camera->GetYOffset());

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
		myParticles->Add((float)cursorX, (float)cursorY - 55, ParticleLife, ParticleStartingColor, ParticleDyingColor, glm::vec2(ParticleSize, ParticleSize));
	
	//setting camera position based on input
	camera->SetPosition(cameraX, cameraY);
	camera->SetZoom(cameraZoom);

	myParticles->Update();
}

void PlayGround::OnRender()
{
	renderer->Clear();

	renderer->DrawQuad(*tex, glm::vec2(64.0f, 64.0f));
	renderer->DrawQuad(*subTex, glm::vec2(64.0f + 128.0f, 64.0f));
	renderer->DrawQuad(glm::vec4(1.0f, 1.0f, 0.0f, 0.7f), glm::vec2(64.0f + 128.0f + 128.0f, 64.0f), glm::vec2(128.0f, 128.0f));
	renderer->DrawQuad(*tex, glm::vec2(64.0f + 128.0f + 128.0f + 128.0f, 64.0f));

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

}