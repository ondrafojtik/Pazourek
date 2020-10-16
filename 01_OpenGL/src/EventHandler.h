#include <stdio.h>
#include <GLFW/glfw3.h>

class EventHandler
{
public:
	EventHandler() = delete;

	static void cursor_pos_callback(GLFWwindow* window, double mouseX, double mouseY)
	{
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		printf("cursorPos: %d, %d\n", (int)x, (int)y);
	}

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if ((key == GLFW_KEY_W) && (action == GLFW_PRESS))
			printf("pressed W");
	}


};