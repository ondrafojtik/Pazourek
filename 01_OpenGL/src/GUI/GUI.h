#pragma once
#include <vector>
#include <string>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace PZ
{

	struct GUI_borders
	{
		glm::vec3 top_left = glm::vec3(0.0f);
		glm::vec3 bot_right = glm::vec3(0.0f);
	};

	struct GUI_text
	{
		std::string text = "";
		glm::vec3 position;
	};

	struct GUI
	{
		
		GUI(glm::vec3 _position);

		void Text(std::string text);

		GUI_borders get_borders();
		std::vector<GUI_text> get_text();

	private:
		std::vector<GUI_text> drawable_text;
		

		glm::vec3 position;
		int line_number = 0; 
		float line_height = 60.0f; // should scale with font..
		float max_line_width = 300.0f;
		float font_render_step = 30.0f;

		// borders
		GUI_borders borders;

	};



}