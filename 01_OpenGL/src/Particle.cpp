#include "Particle.h"

Particle::Particle(float xPos, float yPos, float width, float height, glm::vec4 startingColor, glm::vec4 dyingColor, float life, float dyingSpeed)
	: m_xPos(xPos), m_yPos(yPos), m_Width(width), m_Height(height), m_startingColor(startingColor), m_dyingColor(dyingColor), m_life(life), m_dyingSpeed(dyingSpeed), m_Color(startingColor)
{
	m_Sprite = new Sprite(m_xPos, m_yPos, m_Width, m_Height, m_Color, "src/res/shaders/Basic.shader");
	m_Velocity = glm::vec2((rand() % 100) - 50, (rand() % 100) - 50);
}

Particle::Particle(float xPos, float yPos, float width, float height, glm::vec4 startingColor, glm::vec4 dyingColor, float life)
{
	Particle(xPos, yPos, width, height, startingColor, dyingColor, life, 0.008f);
}

Particle::Particle(float xPos, float yPos, float width, float height, glm::vec4 startingColor, glm::vec4 dyingColor)
{
	Particle(xPos, yPos, width, height, startingColor, dyingColor, 100.0f, 0.008f);
}

Particle::~Particle()
{
	//delete m_Sprite;
	//std::cout << "destroying particle! \n";
}

void Particle::OnUpdate()
{
	//m_Sprite->m_Shader->Bind();
	
	m_Color = glm::vec4(m_Color.x - ((m_startingColor.x - m_dyingColor.x) / m_life),
		m_Color.y - ((m_startingColor.y - m_dyingColor.y) / m_life),
		m_Color.z - ((m_startingColor.z - m_dyingColor.z) / m_life),
		m_Color.a - m_dyingSpeed);
	m_Sprite->MoveSpriteBy(m_Velocity.x * m_Speed / 100, m_Velocity.y * m_Speed / 100);
	m_Sprite->SetColor(m_Color);

}