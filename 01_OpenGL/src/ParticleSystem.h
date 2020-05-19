#pragma once
#include <vector>
#include "Particle.h"

class ParticleSystem
{
private: 
	std::vector<Particle> m_Particles;

public:
	ParticleSystem();
	~ParticleSystem();

	void AddObject(const Particle& particle);
	//optimalization thing
	void AddObject(float xPos, float yPos, float ParticleSizeX, float ParticleSizeY, glm::vec4 ParticleStartingColor, glm::vec4 ParticleDyingColor, float ParticleLife,
		std::string particleShaderPath);

	void OnUpdate();

	std::vector<Particle>& GetParticles() { return m_Particles; }
};