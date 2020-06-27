#pragma once

#include <iostream>

#include "GL/glew.h"
#include "Camera.h"
#include "ParticleSystem.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

struct RenderData
{
	const int vertexCount = 4;

<<<<<<< HEAD
	glm::vec2* positions = nullptr;
	glm::vec2* texCoords = nullptr;

=======
	glm::vec2 *positions = nullptr;
	glm::vec2 *texCoords = nullptr;
	glm::mat4 transform;
	
>>>>>>> origin/master
	unsigned int vao;
	VertexBuffer* vb = nullptr;
	VertexBufferLayout layout;
	VertexArray va;
	IndexBuffer* ib = nullptr;
	Shader* shader = nullptr;

<<<<<<< HEAD
	void Init()
	{
		glm::vec2 l_positions[] = {
		{ -0.5f, -0.5f },
		{  0.5f, -0.5f },
		{  0.5f,  0.5f },
		{ -0.5f,  0.5f },
		};

		glm::vec2 l_coords[] = {
			{ 0.0f, 0.0f },
			{ 1.0f, 0.0f },
			{ 1.0f, 1.0f },
			{ 0.0f, 1.0f },
		};
		positions = l_positions;
		texCoords = l_coords;

		unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
		};

		GLCall(glGenVertexArrays(1, &vao));
		GLCall(glBindVertexArray(vao));

=======
	float* GetPositionBuffer() 
	{
>>>>>>> origin/master
		float pos[(2 + 2) * 4];
		for (int i = 0; i < vertexCount; i++)
		{
			pos[i * vertexCount + 0] = positions[i].x;
			pos[i * vertexCount + 1] = positions[i].y;
<<<<<<< HEAD
			pos[i * vertexCount + 2] = texCoords[i].x;
			pos[i * vertexCount + 3] = texCoords[i].y;
		}

		vb = new VertexBuffer(pos, 4 * 4 * sizeof(float));

		layout.Push<float>(2);
		layout.Push<float>(2);

		va.AddBuffer(*vb, layout);

		ib = new IndexBuffer(indices, 6);

		shader = new Shader("src/res/shaders/Basic.shader");

	}

	void RefreshData()
	{
		float pos[(2 + 2) * 4];
		for (int i = 0; i < vertexCount; i++)
		{
			pos[i * vertexCount + 0] = positions[i].x;
			pos[i * vertexCount + 1] = positions[i].y;
			pos[i * vertexCount + 2] = texCoords[i].x;
			pos[i * vertexCount + 3] = texCoords[i].y;
		}
		vb->RefreshBuffer(pos);
	}

};
=======
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

>>>>>>> origin/master

class Renderer 
{
private:
	Camera* m_Camera;
	RenderData data;
public:
<<<<<<< HEAD
	void DrawQuad(Texture& texture, glm::vec2 position);
	
=======
	
	void DrawQuad(Texture& texture, glm::vec2 position);

	
	//passing in camera doesnt make any sence, you should update projectionMatrix elsewhere!
>>>>>>> origin/master
	Renderer(Camera *camera);

	void DrawSprite(Sprite *m_Sprite);
	void DrawParticles(const std::vector<Particle>& particles);
	void Clear() const; 
};
