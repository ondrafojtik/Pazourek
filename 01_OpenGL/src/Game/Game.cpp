#include "Game.h"

#include "imgui\imgui.h"
#include "imgui\imgui_impl_glfw_gl3.h"

void Game::Init()
{
	camera = new Camera();
	//renderer = new Renderer(camera);
	renderer = new BatchRenderer(camera);
}

void Game::OnUpdate()
{
	renderer->Clear();

	renderer->ResetStats();
	renderer->StartBatch();
	
	// 262 144
	int dim_x = 512;
	int dim_y = 512;
	for (int y = 0; y < dim_y; y++)
		for (int x = 0; x < dim_x; x++)
			renderer->DrawColor(x, y, glm::vec4(1.0f));

	//for (int i = 0; i < 1000; i++)
	//	renderer->DrawColor(0 + i, 100, glm::vec4(1.0f));
	
	renderer->EndBatch();

}

void Game::OnImGuiUpdate()
{
	glfwGetCursorPos(window->GetWindow(), &mouse_pos.x, &mouse_pos.y);

	ImGui::Text("Mouse pos: %f, %f", (float)mouse_pos.x, (float)mouse_pos.y);
	ImGui::Text("Quad count: %.0f", (float)renderer->quad_count);
	ImGui::Text("Draw count: %.0f", (float)renderer->draw_count);

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

}