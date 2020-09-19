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

void Renderer::DrawCube(Texture& texture, glm::vec3 position, float rotation, float xAxes, float yAxes, float zAxes, const glm::vec3& lightPos)
{
	texture.Bind();

	glm::vec2 scale = glm::vec2(1.0f, 1.0f);

	glm::mat4 transform = glm::translate(glm::mat4(1.0f), { position.x, position.y, position.z })
		* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { xAxes, yAxes, zAxes })
		* glm::scale(glm::mat4(1.0f), { scale.x, scale.y, 1.0f });

	data.vb->Bind();
	data.va.Bind();
	data.ib->Bind();
	data.shaders["basic"]->Bind();
	data.shaders["basic"]->SetUniformMat4f("u_Proj", m_Camera->GetProjection());
	data.shaders["basic"]->SetUniformMat4f("u_Transform", transform);
	data.shaders["basic"]->SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
	data.shaders["basic"]->SetUniform4f("u_ColorElement", 1.0f, 1.0f, 1.0f, 1.0f);
	data.shaders["basic"]->SetUniform3f("u_lightPos0", lightPos.x, lightPos.y, lightPos.z);
	//normals debug
	//GLCall(glDrawElements(GL_LINES, data.ib->GetCount(), GL_UNSIGNED_INT, (void*)(sizeof(float)*5)));
	GLCall(glDrawElements(GL_TRIANGLES, data.ib->GetCount(), GL_UNSIGNED_INT, nullptr));
	data.vb->Unbind();
	data.va.Unbind();
	data.ib->Unbind();
	data.shaders["basic"]->Unbind();
	texture.Unbind();

}

void Renderer::DrawLight(const glm::vec4& color, glm::vec3 position, float rotation, float xAxes, float yAxes, float zAxes, const glm::vec3& lightPos)
{
	blank->Bind();

	glm::vec2 scale = glm::vec2(1.0f, 1.0f);

	glm::mat4 transform = glm::translate(glm::mat4(1.0f), { position.x, position.y, position.z })
		* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { xAxes, yAxes, zAxes })
		* glm::scale(glm::mat4(1.0f), { scale.x, scale.y, 1.0f });

	data.vb->Bind();
	data.va.Bind();
	data.ib->Bind();
	data.shaders["basic"]->Bind();
	data.shaders["basic"]->SetUniformMat4f("u_Proj", m_Camera->GetProjection());
	data.shaders["basic"]->SetUniformMat4f("u_Transform", transform);
	data.shaders["basic"]->SetUniform4f("u_Color", color.r, color.g, color.b, color.a);
	data.shaders["basic"]->SetUniform4f("u_ColorElement", 1.0f, 1.0f, 1.0f, 1.0f);
	data.shaders["basic"]->SetUniform3f("u_lightPos0", lightPos.x, lightPos.y, lightPos.z);
	//normals debug
	//GLCall(glDrawElements(GL_LINES, data.ib->GetCount(), GL_UNSIGNED_INT, (void*)(data.layout.GetStride())));
	GLCall(glDrawElements(GL_TRIANGLES, data.ib->GetCount(), GL_UNSIGNED_INT, nullptr));
	data.vb->Unbind();
	data.va.Unbind();
	data.ib->Unbind();
	data.shaders["basic"]->Unbind();
	blank->Unbind();

}
void Renderer::Clear() const
{
	GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}
