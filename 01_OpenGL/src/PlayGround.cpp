#include "PlayGround.h"
#include "Enemy.h"

void PlayGround::OnAttach()
{
	EventHandler::camera = camera;
	//EventHandler::mouseRay = worldRay;

	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double mouseXPos,
		double mouseYPos)
		-> void {EventHandler::cursor_pos_callback(window, mouseXPos, mouseYPos); });
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
	l0.type = LightType::Directional;
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

	// test

	for (int i = 0; i < 5; i++)
	{
		if (Random::Float() > 0.5f)
		{
			glm::vec3 p1 = glm::vec3(Random::Float() * 10, Random::Float() * 10 + 5, Random::Float() * 10);
			glm::vec3 p2 = glm::vec3(Random::Float() * 10, Random::Float() * 10 + 5, Random::Float() * 10);
			glm::vec3 p3 = glm::vec3(Random::Float() * 10, Random::Float() * 10 + 5, Random::Float() * 10);
			glm::vec3 p4 = glm::vec3(Random::Float() * 10, Random::Float() * 10 + 5, Random::Float() * 10);
			glm::mat4x3 bezier = {
				p1.x, p1.y, p1.z,
				p2.x, p2.y, p2.z,
				p3.x, p3.y, p3.z,
				p4.x, p4.y, p4.z
			};
			Object* o = new Enemy(bezier);
			OM->Add(*o);
		}
		else
		{
			glm::vec3 p1 = glm::vec3(Random::Float() * 10, Random::Float() * 10 + 5, Random::Float() * 10);
			glm::vec3 p2 = glm::vec3(Random::Float() * 10, Random::Float() * 10 + 5, Random::Float() * 10);
			glm::vec3 p3 = glm::vec3(Random::Float() * 10, Random::Float() * 10 + 5, Random::Float() * 10);
			glm::vec3 p4 = glm::vec3(Random::Float() * 10, Random::Float() * 10 + 5, Random::Float() * 10);
			glm::mat4x3 bezier = {
				p1.x, p1.y, p1.z,
				p2.x, p2.y, p2.z,
				p3.x, p3.y, p3.z,
				p4.x, p4.y, p4.z
			};
			Object* o = new Ally(bezier);
			OM->Add(*o);
		}
	}
	EventHandler::camera = camera;
	EventHandler::object_manager = OM;

}

void PlayGround::OnDetach()
{
    delete camera;
    delete renderer;
    delete alonso;
    delete tex;
    delete skyBox;
    // delete diffuse;
    // delete specular;
    // delete normal;
    // delete ao;
    // delete roughness;
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

	t += 0.002f * direction;
	if (t > 1)
		direction = -1;
	if (t < 0)
		direction = 1;


	glm::vec4 matOne = glm::vec4(t * t * t, t * t, t, 1);

	glm::mat4 matTwo = {
		-1,  3, -3, 1,
		 3, -6,  3, 0,
		-3,  3,  0, 0,
		 1,  0,  0, 0
	};

	glm::mat4x3 matThree = {
		0, 5, 2,
		0, 5, 12,
		10, 5, 12,
		10, 5, 2
	};

	glm::vec3 final = (matThree * matTwo) * matOne;


	//lights[0].position = final;

	r += 1;
	OM->GetObjects()[0]->Rotate(r, { 1, 0, 0 });
}

void PlayGround::OnRender()
{
	renderer->Clear();
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glStencilFunc(GL_ALWAYS, 0, GL_REPLACE);

    renderer->DrawCube(*skyBox, camera->GetPosition(), { 1, 1, 1 }, 0, 0, 0, 1);
	renderer->DrawMap(*map, { 0, 0, 0 }, lights, drawNormals);
	renderer->DrawLight(lights[0]);
	renderer->DrawLight(lights[1]);


	//renderer->DrawModel(*diffuse, *specular, *normal, *ao, *roughness, { 5, 5, 2 }, lights, ambientStrength, shininess, *model);

	renderer->DrawLine({ EventHandler::mouseRay->originPoint }, { EventHandler::mouseRay->destPoint });

	for (Object* o : OM->GetObjects())
	{
		glStencilFunc(GL_ALWAYS, o->GetID(), GL_REPLACE);
		o->Move(0.01f);
		renderer->DrawObject(*o);
	}

    // rendering font
    char test_char = 'C';
    renderer->DrawChar(*font, test_char, glm::vec3(0, 5, 0), glm::vec3(1.0f));

    std::string test_text = "TOHLE JE TEST_123?!%.";
    renderer->DrawFont(*font, test_text, glm::vec3(0, 8, 0), glm::vec3(0.0f));
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
	ImGui::Checkbox("Show normals", &drawNormals);
	if (ImGui::Button("Recalc map"))
	{
		map->Recalc();
	}
	ImGui::End();


}
