#pragma once
#include <vector>
#include <string>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <chrono>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <GLFW/glfw3.h>

#include "GUI_theme.h"

namespace PZ
{

	static std::string float_to_string(const float& x, const int precision = 1)
	{
		static std::ostringstream ss;
		ss.str("");
		ss << std::fixed << std::setprecision(precision) << x;
		return ss.str();
	}

	struct FPS
	{
		float framerate = 0;
		float fps = 0;
		std::string fps_str = "";
	};

	struct GUI_fps
	{
	private:
		float counter = 0;
		std::chrono::high_resolution_clock::time_point start;
		std::chrono::high_resolution_clock::time_point now;
		
	public:
		FPS fps{};

		void reset()
		{
			counter = 0;
			start = std::chrono::high_resolution_clock::now();
			now = std::chrono::high_resolution_clock::now();
		}

		void update()
		{
			counter += 1;
			now = std::chrono::high_resolution_clock::now();

			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count();
			if (duration >= 100) 
			{
				fps.framerate = 100 / counter;
				fps.fps = 1000 / fps.framerate;
				fps.fps_str = float_to_string(fps.fps, 1);
				reset();
			}

		}

	};

	struct GUI_mouse_state
	{
		double pos_x = -1;
		double pos_y = -1;

		int button = -1;
		int action = -1;
		int mode = -1;
	};

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

	struct GUI_button
	{
		glm::vec3 top_left = glm::vec3(0.0f);
		glm::vec3 bot_right = glm::vec3(0.0f);

		std::string label = "";
		bool* value;
	};

	struct GUI
	{
		
		GUI(glm::vec3 _position);

		void CreateContext(GLFWwindow* window);
		void Clear();
		void Update();
		void Text(std::string text);
		// button as in toggle..
		void Button(std::string label, bool* value);

		GUI_borders get_borders();
		std::vector<GUI_text> get_text();
		std::vector<GUI_button> get_buttons();

		// utils
		FPS Get_FPS();
		static GUI_mouse_state mouse_state;

	private:
		std::vector<GUI_text> drawable_text;
		std::vector<GUI_button> active_buttons;
		
		static void cursor_pos_callback(GLFWwindow* window, double mouseX, double mouseY);
		static void mouse_button_callback(GLFWwindow* window, int button, int action, int mode);

		glm::vec3 position;
		int line_number = 0; 
		float line_height = 60.0f; // should scale with font..
		float max_line_width = 300.0f;
		float font_render_step = 32.0f;

		// borders
		GUI_borders borders;

		// utils
		GUI_fps fps;

		// buttons
		void update_buttons();

	};



}