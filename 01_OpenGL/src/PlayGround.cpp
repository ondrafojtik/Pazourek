#include "PlayGround.h"

void PlayGround::OnAttach()
{
	lightPos = glm::vec3(5, 2, -15);
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
	
	//lightPos.z += 0.1f;
	
	for (int y = 1; y < 10; y++)
		for (int x = 0; x < 10; x++)
			renderer->DrawCube(*grass, { x, y, 0 }, 0, 1, 1, 1, lightPos);

	for (int x = 0; x < 10; x++)
		for (int z = 0; z < 10; z++)
			renderer->DrawCube(*grass, {x, 0, -z}, 0, 1, 1, 1, lightPos);
			
	//render light cube
	//renderer->DrawLight(glm::vec4(1.0f), lightPos, 0, 1, 1, 1, lightPos);

}

void PlayGround::ImGuiOnUpdate()
{
	ImGui::Begin("Debug");
	ImGui::Checkbox("Enable mouse movement", &mouseMovement);
	ImGui::SliderFloat("LightX", &lightPos.x, -10.0f, 10.0f);
	ImGui::SliderFloat("LightY", &lightPos.y, -10.0f, 10.0f);
	ImGui::SliderFloat("LightZ", &lightPos.z, -10.0f, 10.0f);

	ImGui::End();


}