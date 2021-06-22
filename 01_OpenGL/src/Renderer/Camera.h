#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

struct Camera
{
	Camera();

	//////////////////////////////////////////////
	glm::mat4 projection = glm::mat4(1.0f);

};