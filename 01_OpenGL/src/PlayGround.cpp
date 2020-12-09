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
	
	Light l0;
	l0.color = glm::vec3(1.0f);
	l0.position = glm::vec3(5, 5, 8);
	l0.type = LightType::Point;
	l0.lightDir = glm::vec3(0.0f, 0.0f, -1.0f);
	l0.cutoff = 12.0f;
	lights[0] = l0; 
	
	Light l1;
	l1.color = glm::vec3(0.5f);
	l1.position = glm::vec3(5, 5, -10);
	l1.type = LightType::Point;
	l1.lightDir = glm::vec3(0.0f, 0.0f, 1.0f);
	l1.cutoff = 12.0f;
	lights[1] = l1;
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
    
	//lights[0].lightDir = EventHandler::mouseRay->get_normalized_ray();
	//lights[0].position = EventHandler::mouseRay->originPoint;
}

void PlayGround::OnRender()
{
	renderer->Clear();
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    // render map here
	if (showDebugBoxes)
	{
		for (VertexInfo p : map->vertices)
		    renderer->DrawColor(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), { p.position.x, (p.position.y * map->scale.y), p.position.z }, 0, 1, 1, 1);
	}
	
    renderer->DrawCube(*skyBox, camera->GetPosition(), { 1, 1, 1 }, 0, 0, 0, 1);
	renderer->DrawMap(*map, { 0, 0, 0 }, lights);
	renderer->DrawLight(lights[0]);
	renderer->DrawLight(lights[1]);

	//renderer->DrawModel(*diffuse, *specular, *normal, *ao, *roughness, { 5, 5, 2 },
	//	lights, ambientStrength, shininess, *model);
	//render light cube
	
	renderer->DrawLine({ EventHandler::mouseRay->originPoint }, { EventHandler::mouseRay->destPoint });

	//double x, y;
	//glfwGetCursorPos(window, &x, &y);
	//unsigned int _index;
	//glReadPixels(x, glm::abs(y - 540), 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &_index);
	//std::cout << "stencil: " << _index << std::endl;

    
}

void PlayGround::ImGuiOnUpdate()
{
	ImGui::Begin("Debug");
    ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
	ImGui::SliderFloat("LightX", &lights[0].position.x, -20.0f, 20.0f);
	ImGui::SliderFloat("LightY", &lights[0].position.y, -20.0f, 20.0f);
	ImGui::SliderFloat("LightZ", &lights[0].position.z, -20.0f, 20.0f);
	ImGui::Separator();
	ImGui::SliderFloat("ambientStrength", &ambientStrength, 0.0f, 1.0f);
	ImGui::ColorEdit3("lightColor", glm::value_ptr(lights[0].color));
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
