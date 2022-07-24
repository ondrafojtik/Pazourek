#include "Game.h"

#include "imgui\imgui.h"
#include "imgui\imgui_impl_glfw_gl3.h"

void Game::Init()
{
	camera = new Camera();
	b_renderer = new BatchRenderer(camera);
	renderer = new Renderer(camera);

	font = new FontSheet("src/res/textures/font_sheet_5.png");
}

void Game::OnUpdate()
{
	
	renderer->Clear();


	//renderer->DrawColor(mouse_pos.x, mouse_pos.y);
	renderer->DrawText(*font, "ahoj", {50.0f, 50.0f, 1.0f}, {1.0f, 1.0f, 0.0f});
	
}

void Game::OnImGuiUpdate()
{
	glfwGetCursorPos(window->GetWindow(), &mouse_pos.x, &mouse_pos.y);

	ImGui::Text("Mouse pos: %f, %f", (float)mouse_pos.x, (float)mouse_pos.y);
	ImGui::Text("Quad count: %.0f", (float)b_renderer->quad_count);
	ImGui::Text("Draw count: %.0f", (float)b_renderer->draw_count);

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

}









/**************************** BATCH RENDERER TEST  ****************************/
/*  
	b_renderer->Clear();

	b_renderer->ResetStats();
	b_renderer->StartBatch();

	// 262 144
	int dim_x = 512;
	int dim_y = 512;
	for (int y = 0; y < dim_y; y++)
		for (int x = 0; x < dim_x; x++)
			b_renderer->DrawColor(x, y, glm::vec4(1.0f));

	b_renderer->EndBatch();
	*/