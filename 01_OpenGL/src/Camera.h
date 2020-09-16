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
};

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
	float m_Zoom = 60;
	AspectRatio ar = { 1,1 };

public: 
	Camera(float left, float right, float bottom, float top);
	~Camera();

	void SetPosition(float xPos, float yPos);
	void SetZoom(float Zoom);
	void RecalculateVP();

	inline glm::mat4 GetProjection() const { return ViewProjectionMatrix; }
	inline float GetCameraX() const { return m_xCameraOff; }
	inline float GetCameraY() const { return m_yCameraOff; }
	inline float GetRealLeftPos() const { return ((m_Left + m_xCameraOff) + (m_Zoom * 16)); }
	inline float GetRealRightPos() const { return ((m_Right + m_xCameraOff) - (m_Zoom * 16)); }
	inline float GetRealBottomPos() const { return ((m_Bottom + m_yCameraOff) + (m_Zoom * 9)); }
	inline float GetRealTopPos() const { return ((m_Top + m_yCameraOff) - (m_Zoom * 9)); }

	inline float GetWidth() const { return m_Right - m_Left; }
	inline float GetHeight() const { return m_Top - m_Bottom; }
	inline float GetZoom() const { return m_Zoom; }
	inline float GetXOffset() const { return m_xCameraOff; }  
	inline float GetYOffset() const { return m_yCameraOff; }
public: 
	glm::mat4 ViewProjectionMatrix;
	glm::vec3 position = { 0.0f, 0.0f, 0.0f };
	cameraBounds bounds = { -ar.x * m_Zoom, ar.x * m_Zoom, -ar.y * m_Zoom, ar.y * m_Zoom };
	float rotation = 0.0f;

};