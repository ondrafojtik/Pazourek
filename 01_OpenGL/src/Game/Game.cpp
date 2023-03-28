#include "Game.h"

#include "imgui\imgui.h"
#include "imgui\imgui_impl_glfw_gl3.h"

void Game::Init()
{
	camera = new Camera();
	b_renderer = new BatchRenderer(camera);
	renderer = new Renderer(camera);

	font = new FontSheet("src/res/textures/font_sheet_5.png");
	gui = new PZ::GUI(glm::vec3(50.0f, 50.0f, 1.0f));

	gui->CreateContext(window->GetWindow());
}

// #fix: 

void Game::OnUpdate()
{
	
	renderer->Clear();
	gui->Clear();
	
	gui->Text("AHOJ");
	gui->Text("ahojdasdas");
	gui->Text("TOHLE JE UPPER CASE");
	gui->Text(gui->Get_FPS().fps_str + " fps");
	gui->Button("test.test-test", &test_value);
	gui->Text(std::to_string(test_value));

	gui->Text(std::to_string(font->texture->GetHeight()));

	std::vector<PZ::GUI_text> t = gui->get_text();

	renderer->DrawGUI(*gui, *font);
	
}

void Game::OnImGuiUpdate()
{
	glfwGetCursorPos(window->GetWindow(), &mouse_pos.x, &mouse_pos.y);

	ImGui::Text("Mouse pos: %f, %f", (float)mouse_pos.x, (float)mouse_pos.y);
	ImGui::Text("Quad count: %.0f", (float)b_renderer->quad_count);
	ImGui::Text("Draw count: %.0f", (float)b_renderer->draw_count);

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::Checkbox("test.test-test", &test_value);
	// SliderFloat(const char* label, float* v, float v_min, float v_max, const char* display_format = "%.3f", float power = 1.0f);
	ImGui::SliderFloat("slider", &ftest_value, 0.0f, 1.0f);

	gui->Update();

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