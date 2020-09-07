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
#include <math.h>
#include <array>

#include "Renderer.h" //it already includes camera, texture etc. 
#include "Pathfinder.h"

#include "Map.h"
#include "Animation.h"

static std::string s_grid;

static std::array<Node, 15 * 8> s_nodeGrid;

struct MousePosition
{
	double x, y;
	double GetYInverse() { return (glm::abs(1080.0f - (float)y)); }
};

struct PlayGround
{
	float relativeCursorX;
	float relativeCursorY;

	float cameraX = 0;
	float cameraY = 0;
	
	float cameraZoom = 60;

	float ParticleSize = 30.0f;
	float ParticleLife = 70.0f;
	glm::vec4 ParticleStartingColor = glm::vec4(0.8f, 0.15f, 0.05f, 1.0f);
	glm::vec4 ParticleDyingColor = glm::vec4(0.15f, 0.1f, 0.75f, 1.0f);

	GLFWmonitor* monitor = nullptr;
	GLFWwindow* window = nullptr;

	void OnAttach();
	void OnDetach();

	void OnUpdate();
	void OnRender();
	void ImGuiOnUpdate();
private:
	Camera* camera = new Camera(0, 32, 0, 18);
	Renderer* renderer = new Renderer(camera);

	Shader* shader_basic = new Shader("src/res/shaders/Basic.shader");
	Shader* shader_lightning = new Shader("src/res/shaders/basic_lightning.shader");

	//Texture* tex = new Texture("src/res/textures/medievalRTS_spritesheet@2.png");
	Texture* tex = new Texture("src/res/textures/copy.png");
	
	//Texture* tex = new Texture("src/res/textures/copy.png");
	Texture* player = new Texture("src/res/textures/player1.png");
	Texture* tex_alonso = new Texture("src/res/textures/alonso.jpg");

	SubTexture* m_SubGrass = new SubTexture(*tex, glm::vec2(128.0f, 128.0f), 2, 0);
	SubTexture* m_SubForest = new SubTexture(*tex, glm::vec2(128.0f, 128.0f), 1, 3);
	SubTexture* m_SubDown = new SubTexture(*tex, glm::vec2(128.0f, 128.0f), 5, 5);
	SubTexture* m_SubVertical = new SubTexture(*tex, glm::vec2(128.0f, 128.0f), 0, 0);
	SubTexture* m_SubUp = new SubTexture(*tex, glm::vec2(128.0f, 128.0f), 4, 7);
	SubTexture* m_SubIce = new SubTexture(*tex, glm::vec2(128.0f, 128.0f), 3, 0);
	SubTexture* m_SubTree = new SubTexture(*tex, glm::vec2(128.0f, 128.0f), 4, 1);
	SubTexture* m_SubTex = nullptr;

	Texture* anim = new Texture("src/res/textures/anim_test.png");
	Animation* m_Animation = new Animation(*anim, { 240.0f, 240.0f }, 6, 0.2f);

	std::unordered_map<char, SubTexture*> textures;
	
	ParticleSystem* myParticles = new ParticleSystem();

	//might keep it here just for debugging pathFinder
	bool drawGrid = false;

	//grid as in where I am currently with mouse
	glm::vec2 grid = glm::vec2(0.0f, 0.0f);

	Pathfinder* pathFinder = new Pathfinder();
	bool render_path = false;
	//just def. value so I dont get nullptr..
	Node node_to_render_from = s_nodeGrid[0];

	bool editMode = false;
	SubTexture* m_TextureEditMode = m_SubGrass;
	std::pair<char, SubTexture*> m_EditMode = { 'G', m_SubGrass };

	Map* map = new Map("map.txt");

	float lightning_x = -100;
	float lightning_y = -400;
	float side_x = 1;
	float side_y = 1;

	MousePosition* mouse_position = new MousePosition();

};