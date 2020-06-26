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

void Renderer::DrawQuad(Texture& texture, glm::vec3 position)
{
	RenderData data;
	//i think its in degrees
	float rotation = 0;
	glm::vec2 scale = glm::vec2(50.0f, 50.0f);

	data.transform = glm::translate(glm::mat4(1.0f), { position.x, position.y, position.z })
		* glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
		* glm::scale(glm::mat4(1.0f), { scale.x, scale.y, 1.0f });
	
	glm::vec2 positions[] = {
		{ 0.0f, 0.0f },
		{ 1.0f, 0.0f },
		{ 1.0f, 1.0f },
		{ 0.0f, 1.0f },
	};
	glm::vec2 texCoords[] = {
		{ 0.0f, 0.0f },
		{ 1.0f, 0.0f },
		{ 1.0f, 1.0f },
		{ 0.0f, 1.0f },
	};
	//uve gotta bind everyting, add it to the renderData to make to more readable and editable
	data.positions = positions;
	data.texCoords = texCoords;
	
	//this ull want ot push into the VB (might wanna do it inside RenderInfo?)
	float pos[4 * (2 + 2)]; //2 = "position size" , 2 = "coords" - IDK LOOL 
	for (int i = 0; i < data.vertexCount; i++)
	{
		pos[i * data.vertexCount + 0] = data.positions[i].x;
		pos[i * data.vertexCount + 1] = data.positions[i].y;
		pos[i * data.vertexCount + 3] = data.texCoords[i].x;
		pos[i * data.vertexCount + 4] = data.texCoords[i].y;
	}
	//data.vb = new VB(pos, sizeof(..);

	//data.texture = texture;
	//m_Shader->SetUniformMat4f("u_Transform", transform);
	
	//GLCall(glDrawElements(GL_TRIANGLES, m_IB->GetCount(), GL_UNSIGNED_INT, nullptr));
	


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
