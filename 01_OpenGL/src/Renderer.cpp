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

void Renderer::DrawQuad(Texture& texture, glm::vec2 position, glm::vec2 size)
{
	texture.Bind();

	float rotation = 0.0f;
	glm::vec2 scale = size;

	glm::mat4 transform = glm::translate(glm::mat4(1.0f), { position.x, position.y, 0.0f })
		* glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
		* glm::scale(glm::mat4(1.0f), { scale.x, scale.y, 1.0f });

	glm::vec2 coords[4];
	coords[0] = {0.0f, 0.0f};
	coords[1] = {1.0f, 0.0f};
	coords[2] = {1.0f, 1.0f};
	coords[3] = {0.0f, 1.0f};

	for (int i = 0; i < data.vertexCount; i++)
		data.texCoords[i] = coords[i];
	data.RefreshData();

	data.vb->Bind();
	data.va.Bind();
	data.ib->Bind();
	data.shaders["basic"]->Bind();
	data.shaders["basic"]->SetUniformMat4f("u_Proj", m_Camera->GetProjection());
	data.shaders["basic"]->SetUniformMat4f("u_Transform", transform);
	data.shaders["basic"]->SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
	data.shaders["basic"]->SetUniform4f("u_ColorElement", 1.0f, 1.0f, 1.0f, 1.0f);
	GLCall(glDrawElements(GL_TRIANGLES, data.ib->GetCount(), GL_UNSIGNED_INT, nullptr));
	data.vb->Unbind();
	data.va.Unbind();
	data.ib->Unbind();
	data.shaders["basic"]->Unbind();
	texture.Unbind();

}

void Renderer::DrawQuad(Texture& texture, glm::vec2 position)
{
	texture.Bind();

	float rotation = 0.0f;
	glm::vec2 scale = glm::vec2(128.0f, 128.0f);

	glm::mat4 transform = glm::translate(glm::mat4(1.0f), { position.x, position.y, 0.0f })
		* glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
		* glm::scale(glm::mat4(1.0f), { scale.x, scale.y, 1.0f });

	glm::vec2 coords[4];
	coords[0] = { 0.0f, 0.0f };
	coords[1] = { 1.0f, 0.0f };
	coords[2] = { 1.0f, 1.0f };
	coords[3] = { 0.0f, 1.0f };

	for (int i = 0; i < data.vertexCount; i++)
		data.texCoords[i] = coords[i];
	data.RefreshData();

	data.vb->Bind();
	data.va.Bind();
	data.ib->Bind();
	data.shaders["basic"]->Bind();
	data.shaders["basic"]->SetUniformMat4f("u_Proj", m_Camera->GetProjection());
	data.shaders["basic"]->SetUniformMat4f("u_Transform", transform);
	data.shaders["basic"]->SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
	data.shaders["basic"]->SetUniform4f("u_ColorElement", 1.0f, 1.0f, 1.0f, 1.0f);
	GLCall(glDrawElements(GL_TRIANGLES, data.ib->GetCount(), GL_UNSIGNED_INT, nullptr));
	data.vb->Unbind();
	data.va.Unbind();
	data.ib->Unbind();
	data.shaders["basic"]->Unbind();
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

	//assign data
	for (int i = 0; i < data.vertexCount; i++)
		data.texCoords[i] = texture.texCoords[i];
	data.RefreshData();

	data.vb->Bind();
	data.va.Bind();
	data.ib->Bind();
	data.shaders["basic"]->Bind();
	data.shaders["basic"]->SetUniformMat4f("u_Proj", m_Camera->GetProjection());
	data.shaders["basic"]->SetUniformMat4f("u_Transform", transform);
	data.shaders["basic"]->SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
	data.shaders["basic"]->SetUniform4f("u_ColorElement", 1.0f, 1.0f, 1.0f, 1.0f);
	GLCall(glDrawElements(GL_TRIANGLES, data.ib->GetCount(), GL_UNSIGNED_INT, nullptr));
	data.vb->Unbind();
	data.va.Unbind();
	data.ib->Unbind();
	data.shaders["basic"]->Unbind();
	texture.m_texture->Unbind();
}

void Renderer::DrawQuad(glm::vec4 color, glm::vec2 position, glm::vec2 scale, float rotation)
{
	blank->Bind();

	glm::mat4 transform = glm::translate(glm::mat4(1.0f), { position.x, position.y, 0.0f })
		* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
		* glm::scale(glm::mat4(1.0f), { scale.x, scale.y, 1.0f });

	data.vb->Bind();
	data.va.Bind();
	data.ib->Bind();
	data.shaders["basic"]->Bind();
	data.shaders["basic"]->SetUniformMat4f("u_Proj", m_Camera->GetProjection());
	data.shaders["basic"]->SetUniformMat4f("u_Transform", transform);
	data.shaders["basic"]->SetUniform4f("u_Color", color.r, color.g, color.b, color.a);
	data.shaders["basic"]->SetUniform4f("u_ColorElement", 1.0f, 1.0f, 1.0f, 1.0f);
	GLCall(glDrawElements(GL_TRIANGLES, data.ib->GetCount(), GL_UNSIGNED_INT, nullptr));
	data.vb->Unbind();
	data.va.Unbind();
	data.ib->Unbind();
	data.shaders["basic"]->Unbind();
	blank->Unbind();
}

void Renderer::DrawLighning(glm::vec4 color, glm::vec2 position, glm::vec2 size)
{
	blank->Bind();

	float rotation = 0.0f;
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), { position.x, position.y, 0.0f })
		* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
		* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

	data.vb->Bind();
	data.va.Bind();
	data.ib->Bind();
	data.shaders["lightning"]->Bind();
	data.shaders["lightning"]->SetUniformMat4f("u_Proj", m_Camera->GetProjection());
	data.shaders["lightning"]->SetUniformMat4f("u_Transform", transform);
	data.shaders["lightning"]->SetUniform4f("u_Color", color.r, color.g, color.b, color.a);
	data.shaders["lightning"]->SetUniform4f("u_ColorElement", 1.0f, 1.0f, 1.0f, 1.0f);
	GLCall(glDrawElements(GL_TRIANGLES, data.ib->GetCount(), GL_UNSIGNED_INT, nullptr));
	data.vb->Unbind();
	data.va.Unbind();
	data.ib->Unbind();
	data.shaders["lightning"]->Unbind();
	blank->Unbind();
}


void Renderer::DrawGrid(glm::vec4 color, glm::vec2 position)
{
	grid->Bind();

	float rotation = 0.0f;
	glm::vec2 scale = { 128.0f, 128.0f };

	glm::mat4 transform = glm::translate(glm::mat4(1.0f), { position.x, position.y, 0.0f })
		* glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
		* glm::scale(glm::mat4(1.0f), { scale.x, scale.y, 1.0f });

	//data.vb->Bind();
	data.unchanged_vb->Bind();
	//data.va.Bind();
	data.unchanged_va.Bind();
	data.ib->Bind();
	data.shaders["basic"]->Bind();
	data.shaders["basic"]->SetUniformMat4f("u_Proj", m_Camera->GetProjection());
	data.shaders["basic"]->SetUniformMat4f("u_Transform", transform);
	data.shaders["basic"]->SetUniform4f("u_Color", color.r, color.g, color.b, color.a);
	data.shaders["basic"]->SetUniform4f("u_ColorElement", 1.0f, 1.0f, 1.0f, 1.0f);
	GLCall(glDrawElements(GL_TRIANGLES, data.ib->GetCount(), GL_UNSIGNED_INT, nullptr));
	//data.vb->Unbind();
	data.unchanged_vb->Unbind();
	//data.va.Unbind();
	data.unchanged_va.Unbind();
	data.ib->Unbind();
	data.shaders["basic"]->Unbind();
	grid->Unbind();
}

void Renderer::DrawFont(const FontSheet& sheet, glm::vec2* coords, glm::vec3 color)
{
    sheet.texture->Bind();

    glm::vec2 position = glm::vec2(500.0f, 500.0f);
	float rotation = 0.0f;
	glm::vec2 scale = glm::vec2(128.0f, 128.0f);

	glm::mat4 transform = glm::translate(glm::mat4(1.0f), { position.x, position.y, 0.0f })
		* glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
		* glm::scale(glm::mat4(1.0f), { scale.x, scale.y, 1.0f });

	//assign data
	for (int i = 0; i < data.vertexCount; i++)
		data.texCoords[i] = coords[i];
	data.RefreshData();

	data.vb->Bind();
	data.va.Bind();
	data.ib->Bind();
	data.shaders["basic"]->Bind();
	data.shaders["basic"]->SetUniformMat4f("u_Proj", m_Camera->GetProjection());
	data.shaders["basic"]->SetUniformMat4f("u_Transform", transform);
	data.shaders["basic"]->SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
	data.shaders["basic"]->SetUniform4f("u_ColorElement", 1.0f, 1.0f, 1.0f, 1.0f);
	GLCall(glDrawElements(GL_TRIANGLES, data.ib->GetCount(), GL_UNSIGNED_INT, nullptr));
    data.vb->Unbind();
	data.va.Unbind();
	data.ib->Unbind();
	data.shaders["basic"]->Unbind();
	sheet.texture->Unbind();
}

void Renderer::DrawFont(FontSheet& sheet, std::string text, glm::vec3 color)
{
    glm::vec2 position = glm::vec2(500.0f, 500.0f);
    glm::vec2 scale = glm::vec2(128.0f, 128.0f);
    float rotation = 0.0f;
    float step = 0.0f;

    for (char c : text)
    {
        glm::vec2* coords = sheet.get_coords(c);

	    glm::mat4 transform = glm::translate(glm::mat4(1.0f), { position.x + step, position.y, 0.0f })
		    * glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
		    * glm::scale(glm::mat4(1.0f), { scale.x, scale.y, 1.0f });

		sheet.texture->Bind();
        //assign data
        for (int i = 0; i < data.vertexCount; i++)
            data.texCoords[i] = coords[i];
        data.RefreshData();

        data.vb->Bind();
        data.va.Bind();
        data.ib->Bind();
        data.shaders["basic"]->Bind();
        data.shaders["basic"]->SetUniformMat4f("u_Proj", m_Camera->GetProjection());
        data.shaders["basic"]->SetUniformMat4f("u_Transform", transform);
        data.shaders["basic"]->SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
        data.shaders["basic"]->SetUniform4f("u_ColorElement", 1.0f, 1.0f, 1.0f, 1.0f);
        GLCall(glDrawElements(GL_TRIANGLES, data.ib->GetCount(), GL_UNSIGNED_INT, nullptr));
        data.vb->Unbind();
        data.va.Unbind();
        data.ib->Unbind();
        data.shaders["basic"]->Unbind();
        sheet.texture->Unbind();

        step += 64.0f;
    }
}

void Renderer::Clear() const
{
	GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}
