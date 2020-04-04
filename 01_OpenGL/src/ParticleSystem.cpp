#include "ParticleSystem.h"

ParticleSystem::ParticleSystem()
{}

ParticleSystem::~ParticleSystem()
{}

void ParticleSystem::AddObject(const Particle& particle)
{
	m_Particles.push_back(particle);
}

void ParticleSystem::OnUpdate()
{
	for (int i = 0; i < m_Particles.size(); i++)
	{
		m_Particles[i].OnUpdate();

		if (!m_Particles[i].Alive())
		{
			m_Particles.erase(m_Particles.begin() + i);
			continue;
		}

	}

}