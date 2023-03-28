#include "GUI.h"

PZ::GUI_mouse_state PZ::GUI::mouse_state{};

bool collides(PZ::GUI_button button)
{
	glm::vec3 top_left = button.top_left;
	glm::vec3 bot_right = button.bot_right;

	if (PZ::GUI::mouse_state.pos_x >= top_left.x && PZ::GUI::mouse_state.pos_x <= bot_right.x && PZ::GUI::mouse_state.pos_y >= top_left.y && PZ::GUI::mouse_state.pos_y <= bot_right.y)
		return 1;
	return 0;
}

PZ::GUI::GUI(glm::vec3 _position)
{
	position = _position;
	position.z = 1.0f;

    borders = get_borders();
	
	// utils
	fps.reset();
}

void PZ::GUI::CreateContext(GLFWwindow* window)
{
	// setup mouse context
	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double mouseXPos, double mouseYPos)
		-> void {cursor_pos_callback(window, mouseXPos, mouseYPos); });
	glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mode)
		-> void {mouse_button_callback(window, button, action, mode); });


}

void PZ::GUI::Clear()
{
	drawable_text.clear();
	active_buttons.clear();
	line_number = 0;
}

void PZ::GUI::Update()
{
	fps.update();
	update_buttons();
	
}

void PZ::GUI::Text(std::string text)
{
	PZ::GUI_text t;
	t.text = text;
	t.position = glm::vec3(position.x, position.y + (line_number * line_height), 1.0f);
	drawable_text.push_back(t);
	line_number += 1;
	float len = text.length() * font_render_step;
	if (len > max_line_width) max_line_width = len;
}

void PZ::GUI::Button(std::string label, bool* value)
{
	line_number += 1; 
	float len = label.length() * font_render_step;
	if (len > max_line_width) max_line_width = len;
	
	PZ::GUI_button b{};
	b.top_left = { position.x, line_height * line_number, position.z };
	b.bot_right = { position.x + len, line_height * (line_number + 1), position.z };

	b.label = label;
	b.value = value;

	active_buttons.push_back(b);
}

PZ::GUI_borders PZ::GUI::get_borders()
{
    borders.top_left = glm::vec3(position.x, position.y, 1.0f);
	borders.bot_right = glm::vec3(position.x + max_line_width, position.y + (line_number * line_height) + line_height, 1.0f);
	return borders;
}

std::vector<PZ::GUI_text> PZ::GUI::get_text()
{
	return drawable_text;
}

std::vector<PZ::GUI_button> PZ::GUI::get_buttons()
{
	return active_buttons;
}

PZ::FPS PZ::GUI::Get_FPS()
{
	return fps.fps;
}

void PZ::GUI::cursor_pos_callback(GLFWwindow* window, double mouseX, double mouseY)
{
	GUI::mouse_state.pos_x = mouseX;
	GUI::mouse_state.pos_y = mouseY;

}

void PZ::GUI::mouse_button_callback(GLFWwindow* window, int button, int action, int mode)
{
	// action == 1 -> pressed
	// action == 0 -> release
	GUI::mouse_state.button = button;
	GUI::mouse_state.action = action;
	GUI::mouse_state.mode = mode;
	std::cout << "button: " << GUI::mouse_state.button << " action: " << GUI::mouse_state.action << " mode: " << GUI::mouse_state.mode << "\n";
	std::cout << GUI::mouse_state.pos_x << " " << GUI::mouse_state.pos_y << "\n";
	
}

void PZ::GUI::update_buttons()
{
	// button: 0 action: 0 
	if (GUI::mouse_state.button == 0 && GUI::mouse_state.action == 0)
	{
		// check if we colide with any of the active buttons 
		for (PZ::GUI_button b : active_buttons)
			if (collides(b))
				*b.value = !*b.value;
		GUI::mouse_state.button = -1;
		GUI::mouse_state.action = -1;


	}

}
