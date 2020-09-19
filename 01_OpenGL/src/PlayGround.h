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

	GLFWmonitor* monitor = nullptr;
	GLFWwindow* window = nullptr;

	void OnAttach();
	void OnDetach();

	void OnUpdate();
	void OnRender();
	void ImGuiOnUpdate();
private:
	Camera* camera = new Camera({0, 0, -5}, 70, AspectRatio(16, 9), 0.01f, 100.0f);
	Renderer* renderer = new Renderer(camera);
public:
	float rotation = 0;

	Texture* alonso = new Texture("src/res/textures/alonso.jpg");
	Texture* tex = new Texture("src/res/textures/copy.png");
	SubTexture* sub = new SubTexture(*tex, glm::vec2(128.0f, 128.0f), 2, 0);

	//animation test
	Texture* anim = new Texture("src/res/textures/anim_test.png");
	Texture* grass = new Texture("src/res/textures/minecraft_grass.png");
	Animation* animation = new Animation(*anim, { 240.0f, 240.0f }, 6, 0.2f);
	bool mouseMovement = false;
	
};
