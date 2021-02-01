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

#include "Renderer.h" 
#include "Pathfinder.h"

#include "Map.h"
#include "Animation.h"

#include "EventHandler.h"
#include "RandomMap.h"

#include "ObjectManager.h"

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

	GLFWmonitor* monitor = nullptr;
	GLFWwindow* window = nullptr;

	void OnAttach();
	void OnDetach();

	void OnUpdate();
	void OnRender();
	void ImGuiOnUpdate();
private:
	Camera* camera = new Camera({5, 2, 5}, 70, AspectRatio(16, 9), 0.01f, 100.0f);
	Renderer* renderer = new Renderer(camera);

public:
	float rotation = 0;

	Texture* alonso = new Texture("src/res/textures/alonso.jpg");
	Texture* tex = new Texture("src/res/textures/copy.png");
	
	Texture* skyBox = new Texture("src/res/textures/skyBox.png");

	Texture* diffuse = new Texture("src/res/models/backpack/diffuse.jpg");
	Texture* specular = new Texture("src/res/models/backpack/specular.jpg");
	Texture* normal = new Texture("src/res/models/backpack/normal.png");
	Texture* ao = new Texture("src/res/models/backpack/ao.jpg");
	Texture* roughness = new Texture("src/res/models/backpack/roughness.jpg");


	//animation test
	Texture* grass = new Texture("src/res/textures/minecraft_grass.png");
	//Animation* animation = new Animation(*anim, { 240.0f, 240.0f }, 6, 0.2f);
	float ambientStrength = 0.1f;
	float SpecularStrength = 0.5f;
	int shininess = 128;

    glm::vec3 lightPositions[2];
	glm::vec3 lightColor = glm::vec3(1.0f);
	
	Light lights[2];

	Model* model = nullptr;
    
    RandomMap* map = new RandomMap();
	glm::vec3 map_scale = glm::vec3(5.0f, 1.0f, 5.0f);
	int direction = 1;
	float t = 0.1f;

	ObjectManager* OM = new ObjectManager();
	bool drawNormals = 0;

	float r = 0.0f;
};
