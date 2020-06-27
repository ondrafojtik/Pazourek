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

void Renderer::DrawQuad(Texture& texture, glm::vec2 position)
{
	//i dont think I should just "copy" texture into the RenderData since its literally passed into the function
	texture.Bind();

	RenderData data;
	//i think its in degrees
	float rotation = 0;
	glm::vec2 scale = glm::vec2(50.0f, 50.0f);

	data.transform = glm::translate(glm::mat4(1.0f), { position.x, position.y, 0.0f })
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
	unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
	};
	//uve gotta bind everyting, add it to the renderData to make to more readable and editable
	data.positions = positions;
	data.texCoords = texCoords;
	
	//this ull want ot push into the VB (might wanna do it inside RenderInfo?)
	
	
	//VAO
	GLCall(glGenVertexArrays(1, &data.vao));
	GLCall(glBindVertexArray(data.vao));

	//VB
	/*
	just trying smth
	*/
	float pos[(2 + 2) * 4];
	for (int i = 0; i < data.vertexCount; i++)
	{
		pos[i * data.vertexCount + 0] = positions[i].x;
		pos[i * data.vertexCount + 1] = positions[i].y;
		pos[i * data.vertexCount + 2] = texCoords[i].x;
		pos[i * data.vertexCount + 3] = texCoords[i].y;
	}


	data.vb = new VertexBuffer(pos, 4 * 4 * sizeof(float));

	//Layout
	data.layout.Push<float>(2);
	data.layout.Push<float>(2);
	//std::cout << data.layout.GetElements().size() << std::endl;
	//std::cout << data.layout.GetStride() << std::endl;
	//VA
	data.va.AddBuffer(*data.vb, data.layout);

	//IB
	data.ib = new IndexBuffer(indices, 6);
	//Shader
	data.shader = new Shader("src/res/shaders/Basic.shader");
	
	data.BindData();
	texture.Bind();
	data.shader->SetUniformMat4f("u_Proj", m_Camera->GetProjection());
	data.shader->SetUniformMat4f("u_Transform", data.transform);
	data.shader->SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
	data.shader->SetUniform4f("u_ColorElement", 1.0f, 1.0f, 1.0f, 1.0f);
	GLCall(glDrawElements(GL_TRIANGLES, data.ib->GetCount(), GL_UNSIGNED_INT, nullptr));
	data.UnbindData();

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
