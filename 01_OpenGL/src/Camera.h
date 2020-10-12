#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

struct cameraBounds
{
	float left, right, bottom, top;
	float getWidth() { return right - left; }
	float getHeight() { return top - bottom; };
};

struct AspectRatio
{
	int x, y;

	AspectRatio(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
};

struct Camera
{
	Camera(const glm::vec3& position, float fov, AspectRatio ar, float zNear, float zFar);

	glm::mat4 GetProjection() 
	{ 
		return perspective;
	}

	glm::mat4 GetView() 
	{
		return glm::lookAt(m_Position, m_Position + forward, up);
	}

	glm::vec3 GetPosition() { return m_Position; }

private:
	glm::vec3 m_Position;
	glm::mat4 perspective;
	
	glm::vec3 forward;
	glm::vec3 up;
	
	glm::vec3 rotationProduct;

	glm::dvec2 oldMousePos;
	float speed = 0.2f;



public:
	void MoveUp()			{ m_Position += (speed * up); }
	void MoveDown()			{ m_Position -= (speed * up); }
	void MoveLeft()			{ m_Position -= (rotationProduct * speed); } //move to the side of current "forward" axis
	void MoveRight()		{ m_Position += (rotationProduct * speed); }
	void MoveForward()		{ m_Position += (speed * forward); }
	void MoveBackward()		{ m_Position -= (speed * forward); }

	void mouseUpdate(const glm::dvec2& newMousePosition);

};