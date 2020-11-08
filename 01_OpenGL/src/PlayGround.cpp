#include "PlayGround.h"

void PlayGround::OnAttach()
{
	EventHandler::camera = camera;
	//EventHandler::mouseRay = worldRay;

	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double mouseXPos,
                                        double mouseYPos)
		-> void {EventHandler::cursor_pos_callback(window, mouseXPos, mouseYPos);});
	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode,
                                        int action, int mods)
		-> void {EventHandler::key_callback(window, key, scancode, action, mods); });

	glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, 
										int action, int mode)
		-> void {EventHandler::mouse_button_callback(window, button, action, mode); });

	lightPositions[0] = glm::vec3(5, 5, 8);
	lightPositions[1] = glm::vec3(5, 5, -10);

    //in future ure gonna just pass the "ojb. folder" -> that folder WILL have to include
    //texture files in correct form (AO.png, .. )
	//model = new Model("C:/dev/Pazourek/01_OpenGL/src/res/models/backpack/backpack.obj");

    // init map here..
    map->Init();
	
}

void PlayGround::OnDetach()
{
    delete camera;
    delete renderer;
    delete alonso;
    delete tex;
    delete skyBox;
    //delete diffuse;
    //delete specular;
    //delete normal;
    //delete ao;
    //delete roughness;
    //delete anim;
    delete grass;
    //delete animation;
    //delete model;
}

void PlayGround::OnUpdate()
{
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
	
	//animation->OnUpdate();
	//rotation += 1;
	EventHandler::camera = camera;
	
}

void PlayGround::OnRender()
{
	renderer->Clear();
    // render map here
	if (showDebugBoxes)
	{
		for (VertexInfo p : map->vertices)
		    renderer->DrawColor(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), { p.x, (p.y * map->scale), p.z }, 0, 1, 1, 1);
	}
	renderer->DrawMap(*map, { 0, 0, 0 });
    renderer->DrawCube(*skyBox, { 0, 0, 0 }, { 100, 100, 100 }, 0, 0, 0, 1);

	//renderer->DrawModel(*diffuse, *specular, *normal, *ao, *roughness, { 5, 2, 2 },
	//	lightPositions, ambientStrength, lightColor, shininess, *model);
	//render light cube
	renderer->DrawColor(glm::vec4(lightColor.r, lightColor.g, lightColor.b, 1.0f),
                        lightPositions[0], 0, 1, 1, 1);
	renderer->DrawColor(glm::vec4(1.0f), lightPositions[1], 0, 1, 1, 1);

	renderer->DrawLine({ EventHandler::mouseRay->originPoint }, { EventHandler::mouseRay->destPoint });

}

void PlayGround::ImGuiOnUpdate()
{
	ImGui::Begin("Debug");
    ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
	ImGui::SliderFloat("LightX", &lightPositions[0].x, -20.0f, 20.0f);
	ImGui::SliderFloat("LightY", &lightPositions[0].y, -20.0f, 20.0f);
	ImGui::SliderFloat("LightZ", &lightPositions[0].z, -20.0f, 20.0f);
	ImGui::Separator();
	ImGui::SliderFloat("ambientStrength", &ambientStrength, 0.0f, 1.0f);
	ImGui::ColorEdit3("lightColor", glm::value_ptr(lightColor));
	ImGui::SliderInt("shininess", &shininess, 32, 256);
	ImGui::SliderFloat("SpecularStrength", &SpecularStrength, 0.0f, 1.0f);
	ImGui::Separator();
	ImGui::Checkbox("debug boxes", &showDebugBoxes);
	if (ImGui::Button("Recalc map"))
	{
		map->Recalc();
	}
	ImGui::End();


}
