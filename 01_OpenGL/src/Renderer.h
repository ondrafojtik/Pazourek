#pragma once

#include <iostream>

#include "GL/glew.h"

#include "Sprite.h"
#include "Camera.h"
#include "ParticleSystem.h"

struct RenderData
{
	const int vertexCount = 4;

	glm::vec2 *positions = nullptr;
	glm::vec2 *texCoords = nullptr;
	glm::mat4 transform;
	//VB
	//IB
	//...
};


class Renderer 
{
private:
	Camera* m_Camera;
public:
	
	void DrawQuad(Texture& texture, glm::vec3 position);

	
	//passing in camera doesnt make any sence, you should update projectionMatrix elsewhere!
	Renderer(Camera *camera);

	void DrawSprite(Sprite *m_Sprite);
	void DrawParticles(const std::vector<Particle>& particles);
	void Clear() const; 
};