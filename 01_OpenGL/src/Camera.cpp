#include "Camera.h"

Camera::Camera(float left, float right, float bottom, float top) : m_Left(left), m_Right(right), m_Bottom(bottom), m_Top(top)
{
	m_Proj = glm::ortho(m_Left + m_xCameraOff, m_Right + m_xCameraOff, m_Bottom + m_yCameraOff, m_Top + m_yCameraOff);
}

Camera::~Camera()
{
}

void Camera::SetPosition(float xPos, float yPos)
{
	m_xCameraOff = xPos;
	m_yCameraOff = yPos;
	m_Proj = glm::ortho(
		(m_Left + m_xCameraOff) + (m_Zoom * 16), 
		(m_Right + m_xCameraOff) - (m_Zoom * 16), 
		(m_Bottom + m_yCameraOff) + (m_Zoom * 9), 
		(m_Top + m_yCameraOff) - (m_Zoom * 9));
}

void Camera::SetZoom(float Zoom)
{
	m_Zoom = Zoom;
}
