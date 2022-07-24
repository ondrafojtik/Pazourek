#include "Renderer.h"
#include "GlCall.h"
#include <iostream>


constexpr float cexp_vb[] = 
{
	-0.5f, -0.5f, // left bottom
	 0.5f, -0.5f, // right bottom
	 0.5f,  0.5f, // right top
	-0.5f,  0.5f  // left top
};

constexpr unsigned int cexp_ib[] = 
{
	0, 1, 2, 
	2, 3, 0 
};

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

void Renderer::Clear() const
{
	GLCall(glClearColor(0.1f, 0.15f, 0.22f, 1.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

Renderer::Renderer(Camera* camera_)
{
	camera = camera_;
	shader = new Shader("src/res/shaders/Color_non_batch.shader");
	
	GLCall(glGenVertexArrays(1, &vao));
	GLCall(glBindVertexArray(vao));
	
	vb = new VertexBuffer(cexp_vb, 4 * 2 * sizeof(float)); 
	layout.Push<float>(2);

	va.AddBuffer(*vb, layout);
	ib = new IndexBuffer(cexp_ib, 6);

	shader->Bind();
	vb->Bind();
	ib->Bind();

	
}

void Renderer::DrawColor(float x, float y)
{
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0)) * glm::scale(glm::mat4(1.0f), glm::vec3(100, 100, 1));

	shader = new Shader("src/res/shaders/Color_non_batch.shader");
	shader->Bind();

	float gradient = 1.0f;

	shader->SetUniformMat4f("u_view", view);
	shader->SetUniformMat4f("u_projection", camera->projection);
	//shader->SetUniform1f("u_gradient", gradient);

	GLCall(glDrawElements(GL_TRIANGLES, ib->GetCount(), GL_UNSIGNED_INT, nullptr));

	shader->Unbind();
}


void Renderer::DrawChar(FontSheet& font, char32_t character, glm::vec3 position, glm::vec3 color)
{
    font.texture->Bind();

	shader = new Shader("src/res/shaders/Font.shader");
	shader->Bind();

	shader->Bind();

    float rotation = 0.0f;
    glm::vec3 scale = glm::vec3(75.0f, 75.0f, 1.0f);

	glm::mat4 transform = glm::translate(glm::mat4(1.0f), { position.x, position.y, position.z })
		* glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
		* glm::scale(glm::mat4(1.0f), { scale.x, scale.y, scale.z });


	glm::vec2* vertex_texCoords = new glm::vec2[4];
    vertex_texCoords = font.get_coords(character);

	glm::vec3* vertex_positions = new glm::vec3[4];
	vertex_positions[0] = { -0.5f, -0.5f, 0.0f };
	vertex_positions[1] = { 0.5f, -0.5f, 0.0f };
	vertex_positions[2] = { 0.5f,  0.5f, 0.0f };
	vertex_positions[3] = { -0.5f,  0.5f, 0.0f };

    float vertex_info[(3 + 2) * 4];
    {
        for(int i = 0; i < 4; i++)
        {
            vertex_info[(i * 5) + 0] = vertex_positions[i].x;
            vertex_info[(i * 5) + 1] = vertex_positions[i].y;
            vertex_info[(i * 5) + 2] = vertex_positions[i].z;
            vertex_info[(i * 5) + 3] = vertex_texCoords[i].x;
            vertex_info[(i * 5) + 4] = vertex_texCoords[i].y;
        }
    }

    unsigned int indices[] =
	{
		0, 1, 2,
        2, 3, 0
	};

	delete[] vertex_positions;

	shader->SetUniform4f("u_Color", color.x, color.y, color.z, 1.0f);
	shader->SetUniformMat4f("u_View", transform);
	shader->SetUniformMat4f("u_Projection", camera->projection);
	
	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(2);
    VertexBuffer* vb = new VertexBuffer(vertex_info, sizeof(vertex_info));
    IndexBuffer* ib = new IndexBuffer(indices, 6);
    VertexArray* va = new VertexArray();

    va->AddBuffer(*vb, layout);
    vb->Bind();
    va->Bind();
    ib->Bind();
    GLCall(glDrawElements(GL_TRIANGLES, ib->GetCount(), GL_UNSIGNED_INT, nullptr));

    // cleanup
    vb->Unbind();
    va->Unbind();
    ib->Unbind();
	font.texture->Unbind();
	shader->Unbind();
	delete vb;
    delete ib;
    delete va;

}

void Renderer::DrawText(FontSheet& font, std::string text, glm::vec3 position, glm::vec3 color)
{
	float font_render_step = 0.0f;

	for (char32_t c : text)
	{
		DrawChar(font, c, { position.x + font_render_step, position.y, position.z }, color);
		font_render_step += 30.0f;
	}
}