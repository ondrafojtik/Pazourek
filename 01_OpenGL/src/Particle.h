#pragma once
#include <time.h>

#include "glm/glm.hpp"
#include "glm/gtx/quaternion.hpp"
#include <glm/gtc/constants.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/compatibility.hpp>


#include "Sprite.h"

#include "Random.h"


class Particle
{
private:
	float m_xPos;
	float m_yPos;
	float m_life;
	float m_currLife;
	glm::vec4 m_startingColor;
	glm::vec4 m_dyingColor;
	glm::vec4 m_Color;
	float m_Width;
	float m_Height;
	//value assigned here for testing
	glm::vec2 m_Velocity = glm::vec2(0.0f);
	float m_Speed = 1.0f;
	std::string m_Shader;

	Sprite* m_Sprite;

public:
	Particle(float xPos, float yPos, float width, float height, glm::vec4 startingColor, glm::vec4 dyingColor);
	Particle(float xPos, float yPos, float width, float height, glm::vec4 startingColor, glm::vec4 dyingColor, float life);
	Particle(float xPos, float yPos, float width, float height, glm::vec4 startingColor, glm::vec4 dyingColor, float life, std::string shader);

	~Particle();

	inline float GetXPos() { return m_xPos; }
	inline float GetYPos() { return m_yPos; }
	glm::vec2 GetPositionV2() { return glm::vec2(m_xPos, m_yPos); }
	glm::vec3 GetPositionV3() { return glm::vec3(m_xPos, m_yPos, 0.0f); }
	bool Alive() { return (m_Color.a > 0); }

	inline Sprite* GetSprite() { return m_Sprite; }

	void OnUpdate();
};