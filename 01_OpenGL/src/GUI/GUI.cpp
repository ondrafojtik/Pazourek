#include "GUI.h"


PZ::GUI::GUI(glm::vec3 _position)
{
	position = _position;
	position.z = 1.0f;

    borders = get_borders();
	
	// utils
	fps.reset();
}

void PZ::GUI::Clear()
{
	drawable_text.clear();
	line_number = 0;
}

void PZ::GUI::Update()
{
	fps.update();
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

PZ::FPS PZ::GUI::Get_FPS()
{
	return fps.fps;
}
