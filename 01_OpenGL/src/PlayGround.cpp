#include "PlayGround.h"

void PlayGround::OnAttach()
{
}

void PlayGround::OnDetach()
{
}

void PlayGround::OnUpdate()
{
	
	//I should rly make some sort of event system
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraY += 1.0f;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraX -= 1.0f;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraY -= 1.0f;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraX += 1.0f;
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		cameraZoom = cameraZoom + 0.5f;
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		cameraZoom = cameraZoom - 0.5f;
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
		camera->rotation += 0.1f;

	//setting camera position based on input
	camera->SetPosition(cameraX, cameraY);
	camera->SetZoom(cameraZoom);


	animation->OnUpdate();
}

void PlayGround::OnRender()
{
	renderer->Clear();

	
	rotation += 0.3;
	renderer->DrawQuad(*grass, { 0, 0 }, rotation, 1, 1, 1);

}

void PlayGround::ImGuiOnUpdate()
{
	ImGui::Begin("Debug");
	ImGui::End();


}