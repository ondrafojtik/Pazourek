#include "Camera.h"

Camera::Camera(const glm::vec3& position, float fov, AspectRatio ar, float zNear, float zFar)
	: m_Position(position),
	forward(glm::vec3(0.0f, 0.0f, -1.0f)), up(glm::vec3(0.0f, 1.0f, 0.0f)), rotationProduct(glm::cross(forward, up))
{
	perspective = glm::perspective(fov, (float)ar.x / ar.y, zNear, zFar);
	oldMousePos = glm::dvec2(1920, 1080);
}

void Camera::mouseUpdate(const glm::dvec2& newMousePosition)
{
	glm::dvec2 delta = (oldMousePos - newMousePosition);
	
	float mouseSesitivity = 0.5f;
	rotationProduct = glm::cross(forward, up); //to rotate around!
	glm::mat4 rotationMat = glm::rotate(glm::mat4(1.0f), glm::radians((float)delta.x * mouseSesitivity), up) //creating rot mat
		* glm::rotate(glm::mat4(1.0f), glm::radians((float)delta.y * mouseSesitivity), rotationProduct);

	forward = glm::mat3(rotationMat) * forward; //final product

	oldMousePos = newMousePosition;
}