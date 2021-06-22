#include "DynamicVertexBuffer.h"
#include "GLcall.h"
#include "defines.h"

DynamicVertexBuffer::DynamicVertexBuffer()
{
	GLCall(glGenBuffers(1, &m_RendererID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(dyn_quad::Vertex) * (float)MAX_VERTEX_COUNT, nullptr, GL_DYNAMIC_DRAW));
}

DynamicVertexBuffer::~DynamicVertexBuffer()
{

}

void DynamicVertexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void DynamicVertexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
