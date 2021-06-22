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
	shader = new Shader("src/res/shaders/Basic.shader");
	
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

	float gradient = 1.0f;

	shader->SetUniformMat4f("u_view", view);
	shader->SetUniformMat4f("u_projection", camera->projection);
	shader->SetUniform1f("u_gradient", gradient);

	GLCall(glDrawElements(GL_TRIANGLES, ib->GetCount(), GL_UNSIGNED_INT, nullptr));

}