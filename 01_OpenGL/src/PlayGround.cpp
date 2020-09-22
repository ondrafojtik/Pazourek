#include "PlayGround.h"

void PlayGround::OnAttach()
{
	lightPositions[0] = glm::vec3(5, 5, -10);
	lightPositions[1] = glm::vec3(8, 5, -10);
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
			renderer->DrawCube(*grass, { x, y, 0 }, 0, 1, 1, 1, lightPositions, ambientStrength, lightColor, shininess, SpecularStrength);

	for (int x = 0; x < 10; x++)
		for (int z = 0; z < 10; z++)
			renderer->DrawCube(*grass, {x, 0, -z}, 0, 1, 1, 1, lightPositions, ambientStrength, lightColor, shininess, SpecularStrength);
			
	//render light cube
	renderer->DrawColor(glm::vec4(1.0f), lightPositions[0], 0, 1, 1, 1);
	renderer->DrawColor(glm::vec4(1.0f), lightPositions[1], 0, 1, 1, 1);
}

void PlayGround::ImGuiOnUpdate()
{
	ImGui::Begin("Debug");
	ImGui::Checkbox("Enable mouse movement", &mouseMovement);
	ImGui::SliderFloat("LightX", &lightPositions[0].x, -20.0f, 20.0f);
	ImGui::SliderFloat("LightY", &lightPositions[0].y, -20.0f, 20.0f);
	ImGui::SliderFloat("LightZ", &lightPositions[0].z, -20.0f, 20.0f);
	ImGui::Separator();
	ImGui::SliderFloat("ambientStrength", &ambientStrength, 0.0f, 1.0f);
	ImGui::ColorEdit3("lightColor", glm::value_ptr(lightColor));
	ImGui::SliderInt("shininess", &shininess, 0, 256);
	ImGui::SliderFloat("SpecularStrength", &SpecularStrength, 0.0f, 1.0f);
	ImGui::End();


}