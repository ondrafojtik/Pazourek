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
		camera->MoveForward();
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->MoveLeft();
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->MoveBackward();
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->MoveRight();
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		camera->MoveUp();
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		camera->MoveDown();
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		mouseMovement = !mouseMovement;
	
	if(mouseMovement)
	{
		glm::dvec2 mousePos;
		glfwGetCursorPos(window, &mousePos.x, &mousePos.y);
		camera->mouseUpdate(mousePos);
	}
	animation->OnUpdate();
}

void PlayGround::OnRender()
{
	renderer->Clear();

	
	rotation += 0.3;
	renderer->DrawCube(*grass, { 0, 0 }, rotation, 1, 1, 1);

}

void PlayGround::ImGuiOnUpdate()
{
	ImGui::Begin("Debug");
	ImGui::Checkbox("Enable mouse movement", &mouseMovement);
	ImGui::End();


}