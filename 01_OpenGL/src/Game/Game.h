#pragma once
#include <iostream>
#include "Window.h"
#include "GLcall.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Renderer.h"
#include "Camera.h"
#include "BatchRenderer.h"

struct Game
{
	void Init();

	void OnUpdate();
	void OnImGuiUpdate();

	//////////////////////////////////////////////
	Window* window = nullptr;
	//Renderer* renderer = nullptr;
	BatchRenderer* renderer = nullptr;
	Camera* camera = nullptr;
	
	//////////////////////////////////////////////
	glm::dvec2 mouse_pos;

};