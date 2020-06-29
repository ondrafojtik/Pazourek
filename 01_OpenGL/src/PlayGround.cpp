#include "PlayGround.h"

void PlayGround::OnAttach()
{
	Window window(windowWidth, windowHeight);
	glfwMakeContextCurrent(window.GetWindow());
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
		std::cout << "Error" << std::endl;


	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "glew version: " << glewGetString(GLEW_VERSION) << std::endl;
	std::cout << "glfw version: " << glfwGetVersionString() << std::endl;

	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	//////////////IMGUI/////////////////////
	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(window.GetWindow(), true);
	ImGui::StyleColorsDark();

}

void PlayGround::OnDetach()
{

}

void PlayGround::Update()
{
	//input - make some event system already
	if (glfwGetKey(window.GetWindow(), GLFW_KEY_W) == GLFW_PRESS)
		m_CameraY = m_CameraY + 5;
	if (glfwGetKey(window.GetWindow(), GLFW_KEY_A) == GLFW_PRESS)
		m_CameraX = m_CameraX - 5;
	if (glfwGetKey(window.GetWindow(), GLFW_KEY_S) == GLFW_PRESS)
		m_CameraY = m_CameraY - 5;
	if (glfwGetKey(window.GetWindow(), GLFW_KEY_D) == GLFW_PRESS)
		m_CameraX = m_CameraX + 5;
	if (glfwGetKey(window.GetWindow(), GLFW_KEY_Q) == GLFW_PRESS)
		m_CameraZOOM = m_CameraZOOM - 1;
	if (glfwGetKey(window.GetWindow(), GLFW_KEY_E) == GLFW_PRESS)
		m_CameraZOOM = m_CameraZOOM + 1;
	if (glfwGetKey(window.GetWindow(), GLFW_KEY_F) == GLFW_PRESS)
		myParticles->Add((float)cursorX, (float)cursorY - 55, ParticleLife, ParticleStartingColor, ParticleDyingColor, glm::vec2(ParticleSize, ParticleSize));
}

void PlayGround::Render()
{

}

void PlayGround::ImGuiRender()
{
	ImGui::SliderFloat("ParticleSize", &ParticleSize, 0, 200);
	ImGui::SliderFloat("ParticleLife", &ParticleLife, 0, 500);
	ImGui::ColorEdit4("StartingColor", glm::value_ptr(ParticleStartingColor));
	ImGui::ColorEdit4("DyingColor", glm::value_ptr(ParticleDyingColor));
	ImGui::Text("particleBufferSize: %f", (float)myParticles->buffer.size());
}