#pragma once
#include <iostream>
#include "Window.h"
#include "GLcall.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Renderer.h"
#include "Camera.h"
#include "BatchRenderer.h"
#include "Texture.h"
#include "GUI/GUI.h"

struct Game
{
	void Init();

	void OnUpdate();
	void OnImGuiUpdate();

	//////////////////////////////////////////////
	Window* window = nullptr;
	//Renderer* renderer = nullptr;
	BatchRenderer* b_renderer = nullptr;
	Renderer* renderer = nullptr;
	Camera* camera = nullptr;
	
	//////////////////////////////////////////////
	glm::dvec2 mouse_pos;



	//////////////////////////////////////////////
	/* GUI */
	FontSheet* font = nullptr;
	PZ::GUI* gui = nullptr;

	//////////////////////////////////////////////


};