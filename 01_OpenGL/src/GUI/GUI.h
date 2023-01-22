#pragma once
#include <vector>
#include <string>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <chrono>
#include <iostream>
#include <sstream>
#include <iomanip>


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
		float framerate = 0;

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
				framerate = 100 / counter;
				fps.fps = 1000 / framerate;
				fps.fps_str = float_to_string(fps.fps, 1);
				reset();
			}

		}

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

	struct GUI
	{
		
		GUI(glm::vec3 _position);

		void Clear();
		void Update();
		void Text(std::string text);

		GUI_borders get_borders();
		std::vector<GUI_text> get_text();

		FPS Get_FPS();

	private:
		std::vector<GUI_text> drawable_text;
		

		glm::vec3 position;
		int line_number = 0; 
		float line_height = 60.0f; // should scale with font..
		float max_line_width = 300.0f;
		float font_render_step = 30.0f;

		// borders
		GUI_borders borders;

		// utils
		GUI_fps fps;

	};



}