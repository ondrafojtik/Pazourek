#pragma once

#include <iostream>

#include "GL/glew.h"

#include "Sprite.h"
#include "Camera.h"
#include "ParticleSystem.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

struct RenderData
{
	const int vertexCount = 4;

	glm::vec2 *positions = nullptr;
	glm::vec2 *texCoords = nullptr;
	glm::mat4 transform;
	
	unsigned int vao;
	VertexBuffer* vb = nullptr;
	VertexBufferLayout layout;
	VertexArray va;
	IndexBuffer* ib = nullptr;
	Shader* shader = nullptr;

	float* GetPositionBuffer() 
	{
		float pos[(2 + 2) * 4];
		for (int i = 0; i < vertexCount; i++)
		{
			pos[i * vertexCount + 0] = positions[i].x;
			pos[i * vertexCount + 1] = positions[i].y;
			pos[i * vertexCount + 3] = texCoords[i].x;
			pos[i * vertexCount + 4] = texCoords[i].y;
		}

		return pos;
	}

	void BindData()
	{
		vb->Bind();
		va.Bind();
		ib->Bind();
		shader->Bind();
	}
	void UnbindData()
	{
		vb->Unbind();
		va.Unbind();
		ib->Unbind();
		shader->Unbind();
	}


};


class Renderer 
{
private:
	Camera* m_Camera;
public:
	
	void DrawQuad(Texture& texture, glm::vec2 position);

	
	//passing in camera doesnt make any sence, you should update projectionMatrix elsewhere!
	Renderer(Camera *camera);

	void DrawSprite(Sprite *m_Sprite);
	void DrawParticles(const std::vector<Particle>& particles);
	void Clear() const; 
};