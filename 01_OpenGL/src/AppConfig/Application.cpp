#include "defines.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <GLFW\glfw3native.h>

#include "imgui\imgui.h"
#include "imgui\imgui_impl_glfw_gl3.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>



#include "Game.h"

int main(void)
{
	Game game{};
	game.window = new Window(WINDOW_WIDTH, WINDOW_HEIGHT);
	
	glfwMakeContextCurrent(game.window->GetWindow());
	glfwSwapInterval(0);
	if (glewInit() != GLEW_OK)
		std::cout << "Error" << std::endl;

	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	//////////////IMGUI/////////////////////
	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(game.window->GetWindow(), true);
	ImGui::StyleColorsDark();
	////////////////////////////////////////
	
	game.Init();
	
	while (!glfwWindowShouldClose(game.window->GetWindow()))
	{
		game.OnUpdate();
		
		ImGui_ImplGlfwGL3_NewFrame();
		game.OnImGuiUpdate();

		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

		GLCall(glfwSwapBuffers(game.window->GetWindow()));
		GLCall(glfwPollEvents());
	}
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return 0;
}