#include "BatchRenderer.h"
#include <vector>

BatchRenderer::BatchRenderer(Camera* camera_)
{
	camera = camera_;
	shader = new Shader("src/res/shaders/Basic.shader");

	GLCall(glGenVertexArrays(1, &vao));
	GLCall(glBindVertexArray(vao));

	vb = new DynamicVertexBuffer();

	layout.Push<float>(2);
	layout.Push<float>(4);

	va.AddBuffer(*vb, layout);
	
	unsigned int indices[MAX_INDEX_COUNT];
	uint32_t offset = 0;
	for (int32_t i = 0; i < MAX_INDEX_COUNT; i += 6)
	{
		indices[i + 0] = 0 + offset;
		indices[i + 1] = 1 + offset;
		indices[i + 2] = 2 + offset;

		indices[i + 3] = 2 + offset;
		indices[i + 4] = 3 + offset;
		indices[i + 5] = 0 + offset;

		offset += 4;
	}
	ib = new IndexBuffer(indices, MAX_INDEX_COUNT);

	shader->Bind();
	vb->Bind();
	ib->Bind();

	data_ = new dyn_quad::Vertex[MAX_VERTEX_COUNT];
	data_ptr = data_;
}

void BatchRenderer::Clear()
{
	GLCall(glClearColor(0.1f, 0.15f, 0.22f, 1.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void BatchRenderer::DrawColor(int x, int y, glm::vec4 color)
{
	if (index_count >= MAX_INDEX_COUNT)
	{
		EndBatch();
		StartBatch();
	}
	
	float size = 1;

	data_ptr->position = { x, y + size };
	data_ptr->color = color;
	data_ptr++;

	data_ptr->position = { x + size, y + size };
	data_ptr->color = color;
	data_ptr++;

	data_ptr->position = { x + size, y };
	data_ptr->color = color;
	data_ptr++;

	data_ptr->position = { x, y };
	data_ptr->color = color;
	data_ptr++;

	index_count += 6;
	quad_count += 1;
}

void BatchRenderer::Flush()
{
	//glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)) * glm::scale(glm::mat4(1.0f), glm::vec3(100, 100, 1));
	//lm::mat4 view = glm::scale(glm::mat4(1.0f), glm::vec3(100, 100, 1));
	glm::mat4 view = glm::mat4(1.0f);

	shader->SetUniformMat4f("u_view", view);
	shader->SetUniformMat4f("u_projection", camera->projection);
	
	GLCall(glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, nullptr));

	draw_count += 1;
	index_count = 0;

	data_ptr = data_;

}

void BatchRenderer::StartBatch()
{
	data_ptr = data_;
}

void BatchRenderer::EndBatch()
{
	uint32_t data_size = (uint8_t*)data_ptr - (uint8_t*)data_;
	glBufferSubData(GL_ARRAY_BUFFER, 0, data_size, data_);
	Flush();
}

void BatchRenderer::ResetStats()
{
	draw_count = 0;
	quad_count = 0;
}