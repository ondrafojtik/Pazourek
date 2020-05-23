#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLFW\glfw3native.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>

#include "imgui\imgui.h"
#include "imgui\imgui_impl_glfw_gl3.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "defines.h"
#include "Camera.h"
#include "Renderer.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include <Windows.h>
#include "Window.h"
#include "Particle.h"
#include "ParticleSystem.h"
#include "Random.h"
#include "Colors.h"


float l_WindowWidth = 1920;
float l_WindowHeight = 1080;

float posX = 0;
float posY = 0;

float m_CameraX = 0;
float m_CameraY = 0;
float m_CameraZOOM = 0;

int main(void)
{
	Window window(l_WindowWidth, l_WindowHeight);
	glfwMakeContextCurrent(window.GetWindow());
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
		std::cout << "Error" << std::endl;

	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;


	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	//////////////IMGUI/////////////////////
	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(window.GetWindow(), true);
	ImGui::StyleColorsDark();
	////////////////////////////////////////
	
	const std::string& path0 = "src/res/textures/grass.png";
	const std::string& path1 = "src/res/textures/iu.png";
	const std::string& path3 = "src/res/textures/cobblestone.jpg";
	const std::string& path4 = "src/res/textures/red.png";
	const std::string& path5 = "src/res/textures/braun.jpg";
	const std::string& path6 = "src/res/textures/parcFerme.jpg";
	const std::string& path7 = "src/res/textures/bojack.png";
	const std::string& path8 = "src/res/textures/artifact.png";

	Sprite* mySprite1 = new Sprite(100, 100, 50, 50, path0, "src/res/shaders/Basic.shader");
	Sprite* mySprite2 = new Sprite(200, 100, 50, 58, path1, "src/res/shaders/Basic.shader");
	Sprite* mySprite3 = new Sprite(300, 100, 50, 50, path4, "src/res/shaders/Debug.shader");
	Sprite* mySprite4 = new Sprite(400, 100, 50, 50, path5, "src/res/shaders/Sphere.shader");
	Sprite* mySphere1 = new Sprite(500, 100, 50, 50, path0, "src/res/shaders/Sphere.shader");
	Sprite* mySphere2 = new Sprite(600, 100, 50, 50, path6, "src/res/shaders/Sphere.shader");
	Sprite* Player = new Sprite((l_WindowWidth / 2) - 25, (l_WindowHeight / 2) - 25, 50, 50, path7, "src/res/shaders/Sphere.shader");

	//normal camera
	Camera *camera = new Camera(0.0f, l_WindowWidth, 0.0f, l_WindowHeight);
	//camera when drawing function
	//Camera* camera = new Camera(-384.0f, 384.0f, -216.0f, 216.0f);
	Renderer *renderer = new Renderer(camera);

	ParticleSystem* myParticles = new ParticleSystem();
	
	double cursorX;
	double cursorY;

	float tmpRotation = 0.0f;

	float ParticleSize = 50.0f;
	float ParticleLife = 100.0f;
	float ParticleDyingSpeed = 0.008f;
	glm::vec4 ParticleStartingColor = COLOR::YELLOW;
	glm::vec4 ParticleDyingColor = COLOR::RED;
	bool enableRotation = true;
	bool enableScale = true;
	bool enableCircles = true;
	
	int particleShaderIndex = 0;
	std::string particleShaderPath = "src/res/shaders/Sphere.shader";

	//TRYING TO USE PAZOUREK FOR HIS ORIGINAL PURPOSE
	glm::vec2 *fPos = new glm::vec2(0.0f);
	int fFrom = -100;
	int fTo = 100;
	std::vector<glm::vec2> fPositions;
	bool drawed = false;
	//mapping
	float currPos = fFrom;
	while (currPos <= fTo)
	{
		float fx, fy;
		fx = currPos;
		fy = glm::sin(fx);
		fPositions.push_back(glm::vec2(fx, fy));
		currPos += 0.1;
	}
	mySprite2->SetPivot(CENTER);

	while (!glfwWindowShouldClose(window.GetWindow()))
	{
		//trying mosue input
		//sets the values into cursorX, Y.. 
		glfwGetCursorPos(window.GetWindow(), &cursorX, &cursorY);

		cursorX = (cursorX + camera->GetXOffset());
		cursorY = (glm::abs(1080 - (float)cursorY) + camera->GetYOffset());

		myParticles->OnUpdate();
		
		tmpRotation += 0.03f;
		mySprite2->RotateSprite(tmpRotation);

		//drawing function
		//if(!drawed)
		//{
		//	for (glm::vec2 fPos : fPositions)
		//		renderer->DrawSprite(new Sprite(fPos.x, fPos.y, 0.3f, 0.3f, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), "src/res/shaders/Basic.shader"));
		//	drawed = true;
		//}
		//renderer->DrawSprite(new Sprite(-0.5f, -0.5f, 1.0f, 1.0f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), "src/res/shaders/Basic.shader"));

		renderer->Clear();
		ImGui_ImplGlfwGL3_NewFrame();
	
		//INPUT
		if (glfwGetKey(window.GetWindow(), GLFW_KEY_W) == GLFW_PRESS)
			m_CameraY = m_CameraY + 5;
		if (glfwGetKey(window.GetWindow(), GLFW_KEY_A) == GLFW_PRESS)
			m_CameraX = m_CameraX - 5;
		if (glfwGetKey(window.GetWindow(), GLFW_KEY_S) == GLFW_PRESS)
			m_CameraY = m_CameraY - 5;
		if (glfwGetKey(window.GetWindow(), GLFW_KEY_D) == GLFW_PRESS)
			m_CameraX = m_CameraX + 5;
		if (glfwGetKey(window.GetWindow(), GLFW_KEY_Q) == GLFW_PRESS)
			m_CameraZOOM = m_CameraZOOM - 1;
		if (glfwGetKey(window.GetWindow(), GLFW_KEY_E) == GLFW_PRESS)
			m_CameraZOOM = m_CameraZOOM + 1;
		if (glfwGetKey(window.GetWindow(), GLFW_KEY_F) == GLFW_PRESS)
			myParticles->AddObject((float)cursorX, (float)cursorY - 55, ParticleSize, ParticleSize, ParticleStartingColor, ParticleDyingColor, ParticleLife, particleShaderPath, enableRotation, enableScale);
		
		//CAMERA
		camera->SetPosition(m_CameraX, m_CameraY);
		camera->SetZoom(m_CameraZOOM);
		

		//Particles
		ImGui::SliderFloat("ParticleSize", &ParticleSize, 0, 200);
		ImGui::SliderFloat("ParticleLife", &ParticleLife, 0, 500);
		ImGui::ColorEdit4("StartingColor", glm::value_ptr(ParticleStartingColor));
		ImGui::ColorEdit4("DyingColor", glm::value_ptr(ParticleDyingColor));
		ImGui::Checkbox("Enable rotation", &enableRotation);
		ImGui::Checkbox("Enable scale", &enableScale);
		ImGui::Checkbox("Circles", &enableCircles);

		if(enableCircles)
			particleShaderPath = "src/res/shaders/Sphere.shader";
		else
			particleShaderPath = "src/res/shaders/Basic.shader";

		//renderer->DrawSprite(mySprite1);
		renderer->DrawSprite(mySprite2);
		//renderer->DrawSprite(mySprite3);
		//renderer->DrawSprite(mySprite4);
		//renderer->DrawSprite(mySphere1);
		//renderer->DrawSprite(mySphere2);
		//Player->MoveSprite((camera->GetWidth() / 2) + m_CameraX - 25, (camera->GetHeight()/ 2) + m_CameraY - 25);
		//renderer->DrawSprite(Player);
		renderer->DrawParticles(myParticles->GetParticles());
		
		

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::Text("Cursor X: %f, Y: %f", (float)cursorX, (float)cursorY);

		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

		GLCall(glfwSwapBuffers(window.GetWindow()));
		GLCall(glfwPollEvents());
		}
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	
	glfwTerminate();
	return 0;
}