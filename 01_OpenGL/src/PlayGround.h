#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "imgui\imgui.h"
#include "imgui\imgui_impl_glfw_gl3.h"

#include <glm/gtc/type_ptr.hpp>
#include "glm/vec2.hpp"
#include "glm/vec4.hpp"

#include <unordered_map>
#include <memory>

#include "Renderer.h" //it already includes camera, texture etc. 

struct PlayGround
{
	double cursorX;
	double cursorY;

	float cameraX = 0;
	float cameraY = 0;
	float cameraZoom = 0;

	float ParticleSize = 30.0f;
	float ParticleLife = 15.0f;
	glm::vec4 ParticleStartingColor = glm::vec4(1.0f);
	glm::vec4 ParticleDyingColor = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);

	GLFWmonitor* monitor = nullptr;
	GLFWwindow* window = nullptr;

	void OnAttach();
	void OnDetach();

	void OnUpdate();
	void OnRender();
	void ImGuiOnUpdate();
private:
	Camera* camera = new Camera(0, 1920, 0, 1080);
	Renderer* renderer = new Renderer(camera);
	
	Texture* tex = new Texture("src/res/textures/medievalRTS_spritesheet@2.png");
	
	SubTexture* m_SubGrass = new SubTexture(*tex, glm::vec2(128.0f, 128.0f), 2, 0);
	SubTexture* m_SubForest = new SubTexture(*tex, glm::vec2(128.0f, 128.0f), 1, 3);
	SubTexture* m_SubDown = new SubTexture(*tex, glm::vec2(128.0f, 128.0f), 5, 5);
	SubTexture* m_SubVertical = new SubTexture(*tex, glm::vec2(128.0f, 128.0f), 0, 0);
	SubTexture* m_SubUp = new SubTexture(*tex, glm::vec2(128.0f, 128.0f), 4, 7);
	SubTexture* m_SubTex = nullptr;


	std::unordered_map<char, SubTexture*> textures;
	
	ParticleSystem* myParticles = new ParticleSystem();
	
};