#pragma once
#include "glm/vec2.hpp"
#include "Texture.h"



struct SubTexture
{
	Texture& m_texture;


	SubTexture(Texture& texture, glm::vec2 min, glm::vec2 max);
	Texture& CreateFromCoords

	glm::vec2 GetPosition() { return glm::vec2(m_x, m_y); }

};
