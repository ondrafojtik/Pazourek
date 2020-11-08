#include <stdio.h>
#include <GLFW/glfw3.h>
#include "Camera.h"
#include "MouseRay.h"
#include "glm/vec4.hpp"

#define DEBUG 0

static class EventHandler
{
private:
	static bool mouseEnable;

public:

	EventHandler() = delete;

	static Camera* camera;
	static MouseRay* mouseRay;
	static glm::vec3 originPoint;
	static glm::vec3 destPoint;
	
	static void cursor_pos_callback(GLFWwindow* window, double mouseX, double mouseY)
	{
		if(mouseEnable)
			camera->mouseUpdate({ mouseX, mouseY });

		#if DEBUG
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		printf("cursorPos: %d, %d\n", (int)x, (int)y);
		#endif
	}

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if ((key == GLFW_KEY_E) && (action == GLFW_PRESS))
		{
			mouseEnable = !mouseEnable;
			printf("Mouse rotation toggle! (current state: %i)\n",(int)mouseEnable);
	    }
	}

	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mode)
	{
		if (action == GLFW_PRESS)
		{
			printf("button_callback [%d,%d,%d]\n", button, action, mode);
			glm::dvec2 mouse;
			glfwGetCursorPos(window, &mouse.x, &mouse.y);
			mouseRay->update_camera(camera);
			mouseRay->set_mouse_position(mouse);
			mouseRay->update();
			
		}
	}



};
