#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera 
{
private:
	glm::mat4 m_Proj;
	float m_Left;
	float m_Right;
	float m_Bottom;
	float m_Top;
	float m_xCameraOff = 0;
	float m_yCameraOff = 0;
	float m_Zoom = 0;

public: 
	Camera(float left, float right, float bottom, float top);
	~Camera();

	void SetPosition(float xPos, float yPos);
	void SetZoom(float Zoom);
	inline glm::mat4 GetProjection() { return m_Proj; }
	inline float GetCameraX() { return m_xCameraOff; }
	inline float GetCameraY() { return m_yCameraOff; }
	inline float GetRealLeftPos() { return ((m_Left + m_xCameraOff) + (m_Zoom * 16)); }
	inline float GetRealRightPos() { return ((m_Right + m_xCameraOff) - (m_Zoom * 16)); }
	inline float GetRealBottomPos() { return ((m_Bottom + m_yCameraOff) + (m_Zoom * 9)); }
	inline float GetRealTopPos() { return ((m_Top + m_yCameraOff) - (m_Zoom * 9)); }
};