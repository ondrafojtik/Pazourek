#include "PlayGround.h"

void PlayGround::OnAttach()
{
	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double mouseXPos, double mouseYPos)
		-> void {EventHandler::cursor_pos_callback(window, mouseXPos, mouseYPos);});
	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		-> void {EventHandler::key_callback(window, key, scancode, action, mods); });


	lightPositions[0] = glm::vec3(5, 5, 8);
	lightPositions[1] = glm::vec3(5, 5, -10);

	model = new Model("C:/dev/Pazourek/01_OpenGL/src/res/models/backpack/backpack.obj");
	
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
	renderer->DrawCube(*skyBox, { 0, 0, 0 }, { 100, 100, 100 }, 0, 0, 0, 1);

	renderer->DrawModel(*diffuse, *specular, *normal, *ao, *roughness, { 5, 2, 2 }, lightPositions, ambientStrength, lightColor, shininess, *model);
	//render light cube
	renderer->DrawColor(glm::vec4(lightColor.r, lightColor.g, lightColor.b, 1.0f), lightPositions[0], 0, 1, 1, 1);
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