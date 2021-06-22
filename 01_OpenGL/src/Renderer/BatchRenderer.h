#pragma once
#include "GL/glew.h"

#include "Camera.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "DynamicVertexBuffer.h"

#include <array>
#include "defines.h"

//#include "glm/glm.hpp"
//#include "glm/gtc/matrix_transform.hpp"


struct BatchRenderer
{
private:
	void Flush();

public:
	BatchRenderer(Camera* camera_);
	void Clear();
	
	void StartBatch();
	void EndBatch();
	void ResetStats();

	void DrawColor(int x, int y, glm::vec4 color);
	//////////////////////////////////////////////
	Camera* camera = nullptr;
	Shader* shader = nullptr;

	unsigned int vao;
	DynamicVertexBuffer* vb = nullptr;
	VertexBufferLayout layout;
	VertexArray va;
	IndexBuffer* ib = nullptr;

	//////////////////////////////////////////////
	//std::array<dyn_quad::Vertex, MAX_VERTEX_COUNT> data;
	//dyn_quad::Vertex* buffer = nullptr;

	dyn_quad::Vertex* data_ = nullptr;
	dyn_quad::Vertex* data_ptr = nullptr;

	uint32_t index_count = 0;
	uint32_t quad_count = 0;
	uint32_t draw_count = 0;
};
