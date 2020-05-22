#include "Renderer.h"


//linked to GLCall, might have to deal with later
void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << ")" << function << " " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}

Renderer::Renderer(Camera *camera) : m_Camera(camera) {}

void Renderer::DrawSprite(Sprite *m_Sprite)
{
	m_Sprite->m_Shader->Bind();
	m_Sprite->m_Shader->SetUniformMat4f("u_Proj", m_Camera->GetProjection());
	m_Sprite->OnRender();
}

void Renderer::DrawParticles(const std::vector<Particle>& particles)
{
	for (Particle elem : particles)
	{
		elem.GetSprite()->m_Shader->Bind();
		elem.GetSprite()->m_Shader->SetUniformMat4f("u_Proj", m_Camera->GetProjection());
		elem.GetSprite()->OnRender();
	}
}

void Renderer::Clear() const
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}
