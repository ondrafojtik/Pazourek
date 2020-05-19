#include "ParticleSystem.h"

ParticleSystem::ParticleSystem()
{
	m_Particles.reserve(1000);
}

ParticleSystem::~ParticleSystem()
{}

void ParticleSystem::AddObject(float xPos, float yPos, float ParticleSizeX, float ParticleSizeY, glm::vec4 ParticleStartingColor, glm::vec4 ParticleDyingColor, float ParticleLife,
	std::string particleShaderPath)
{
	m_Particles.emplace_back(xPos, yPos, ParticleSizeX, ParticleSizeY, ParticleStartingColor, ParticleDyingColor, ParticleLife, particleShaderPath);
}

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
		}

	}

}