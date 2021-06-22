#pragma once
#include "GL/glew.h"

#include "Camera.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"

struct Renderer
{
	Renderer(Camera *camera_);
	
	void Clear() const;
	void DrawColor(float x, float y);

	//////////////////////////////////////////////
	Camera* camera = nullptr;
	Shader* shader = nullptr;

	unsigned int vao;
	VertexBuffer* vb = nullptr;
	VertexBufferLayout layout;
	VertexArray va;
	IndexBuffer* ib = nullptr;
	
};
