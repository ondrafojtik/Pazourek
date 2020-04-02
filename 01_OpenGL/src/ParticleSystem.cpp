#include "ParticleSystem.h"

ParticleSystem::ParticleSystem()
{
	m_objects = std::vector<std::unique_ptr<Particle>>();
}

ParticleSystem::~ParticleSystem()
{
	//delete m_objects;
}

void ParticleSystem::AddObject(Particle particle)
{
	//m_objects.push_back(particle);
}

void ParticleSystem::OnUpdate()
{

}