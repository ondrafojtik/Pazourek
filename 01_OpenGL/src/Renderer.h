#pragma once

#include <iostream>

#include "GL/glew.h"

#include "Sprite.h"
#include "Camera.h"
#include "ParticleSystem.h"

class Renderer 
{
private:
	Camera* m_Camera;
public:
	Renderer(Camera *camera);
	void DrawSprite(Sprite *m_Sprite);
	void DrawParticles(const std::vector<Particle>& particles);
	void Clear() const; 
};