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

Renderer::Renderer(Camera *camera) : m_Camera(camera) 
{
	data.Init();
}

void Renderer::DrawQuad(Texture& texture, glm::vec2 position)
{
	texture.Bind();
	
	float rotation = 0.0f;
	glm::vec2 scale = glm::vec2(128.0f, 128.0f);
	
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), { position.x, position.y, 0.0f })
		* glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
		* glm::scale(glm::mat4(1.0f), { scale.x, scale.y, 1.0f });
	
	//std::cout << data.layout.GetElements().size() << std::endl;
	//std::cout << data.layout.GetStride() << std::endl;
	
	data.vb->Bind();
	data.va.Bind();
	data.ib->Bind();
	data.shader->Bind();
	data.shader->SetUniformMat4f("u_Proj", m_Camera->GetProjection());
	data.shader->SetUniformMat4f("u_Transform", transform);
	data.shader->SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
	data.shader->SetUniform4f("u_ColorElement", 1.0f, 1.0f, 1.0f, 1.0f);
	GLCall(glDrawElements(GL_TRIANGLES, data.ib->GetCount(), GL_UNSIGNED_INT, nullptr));
	data.vb->Unbind();
	data.va.Unbind();
	data.ib->Unbind();
	data.shader->Unbind();
	texture.Unbind();

}

void Renderer::DrawQuad(SubTexture& texture, glm::vec2 position)
{
	texture.m_texture->Bind();

	float rotation = 0.0f;
	glm::vec2 scale = glm::vec2(128.0f, 128.0f);

	glm::mat4 transform = glm::translate(glm::mat4(1.0f), { position.x, position.y, 0.0f })
		* glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
		* glm::scale(glm::mat4(1.0f), { scale.x, scale.y, 1.0f });

	//std::cout << data.layout.GetElements().size() << std::endl;
	//std::cout << data.layout.GetStride() << std::endl;
	
	//assign data
	for (int i = 0; i < data.vertexCount; i++)
		data.texCoords[i] = texture.texCoords[i];

	data.RefreshData();

	data.vb->Bind();
	data.va.Bind();
	data.ib->Bind();
	data.shader->Bind();
	data.shader->SetUniformMat4f("u_Proj", m_Camera->GetProjection());
	data.shader->SetUniformMat4f("u_Transform", transform);
	data.shader->SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
	data.shader->SetUniform4f("u_ColorElement", 1.0f, 1.0f, 1.0f, 1.0f);
	GLCall(glDrawElements(GL_TRIANGLES, data.ib->GetCount(), GL_UNSIGNED_INT, nullptr));
	data.vb->Unbind();
	data.va.Unbind();
	data.ib->Unbind();
	data.shader->Unbind();
	texture.m_texture->Unbind();
}

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
