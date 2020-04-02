#pragma once
#include <vector>
#include "Particle.h"

class ParticleSystem
{
private: 
	std::vector<std::unique_ptr<Particle>> m_objects;

public:
	ParticleSystem();
	~ParticleSystem();

	void AddObject(Particle particle);

	void OnUpdate();


};