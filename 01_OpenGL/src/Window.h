#pragma once

#include <GL/glew.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLFW\glfw3native.h>

#include <iostream>

class Window
{
private: 
	GLFWwindow* m_Window;
	GLFWmonitor* m_Monitor;
	float m_WindowWidth;
	float m_WindowHeight;

public:
	Window(float WindowWidth, float WindowHeight);
	~Window();



	inline GLFWwindow* GetWindow() { return m_Window; }
	inline GLFWmonitor* GetMonitor() { return m_Monitor; }
	inline float GetWindowWidth() { return m_WindowWidth; }
	inline float GetWindowHeight() { return m_WindowHeight; }

};
