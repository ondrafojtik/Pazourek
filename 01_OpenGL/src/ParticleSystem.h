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

	void OnUpdate();

	std::vector<Particle>& GetParticles() { return m_Particles; }
};