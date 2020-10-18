#include <stdio.h>
#include <GLFW/glfw3.h>
#include "Camera.h"

#define DEBUG 0

static class EventHandler
{
private:
	static bool mouseEnable;

public:

	EventHandler() = delete;

	static Camera* camera;

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


};
