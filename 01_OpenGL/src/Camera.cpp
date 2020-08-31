#include "Camera.h"

Camera::Camera(float left, float right, float bottom, float top) : m_Left(left), m_Right(right), m_Bottom(bottom), m_Top(top)
{
	m_Proj = glm::ortho(m_Left + m_xCameraOff, m_Right + m_xCameraOff, m_Bottom + m_yCameraOff, m_Top + m_yCameraOff);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), position)
		* glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f });

	ViewProjectionMatrix = m_Proj * view;
}

Camera::~Camera() {}

void Camera::RecalculateVP()
{
	m_Proj = glm::ortho(bounds.left, bounds.right, bounds.bottom, bounds.top);

	glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
		* glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f });
	glm::mat4 view = glm::inverse(transform);

	ViewProjectionMatrix = m_Proj * view;
}

void Camera::SetPosition(float xPos, float yPos)
{
	position.x = xPos;
	position.y = yPos;
	RecalculateVP();
}

void Camera::SetZoom(float Zoom)
{
	m_Zoom = Zoom;
	bounds = { -ar.x * m_Zoom, ar.x * m_Zoom, -ar.y * m_Zoom, ar.y * m_Zoom };
	RecalculateVP();
}
