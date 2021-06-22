#pragma once
#include "glm/vec4.hpp"
#include "glm/vec2.hpp"

namespace dyn_quad
{
	struct Vertex
	{
		glm::vec2 position;
		glm::vec4 color;
	};
}

class DynamicVertexBuffer
{
private:
	unsigned int m_RendererID;
	const void* m_Data;
	unsigned int m_Size;
public:
	DynamicVertexBuffer();
	~DynamicVertexBuffer();

	void Bind() const;
	void Unbind() const;
};