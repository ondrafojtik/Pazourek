#pragma once
#include "imgui\imgui.h"
#include "imgui\imgui_impl_glfw_gl3.h"

#include "Window.h"

class PlayGround
{
private:
	float windowWidth = 1920.0f;
	float windowHeight = 1080.0f;

public:
	void OnAttach();
	void OnDetach();

	void Update();

	void Render();
	void ImGuiRender();
};