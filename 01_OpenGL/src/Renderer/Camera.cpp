#include "Camera.h"
#include "defines.h"

Camera::Camera()
{
	projection = glm::ortho
	(
		0.0f,					(float)WINDOW_WIDTH, 
		(float)WINDOW_HEIGHT,	0.0f,
	   -1.0f,					1.0f
	);
}