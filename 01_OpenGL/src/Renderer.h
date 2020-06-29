#pragma once
#include "GL/glew.h"

#include "Camera.h"
#include "ParticleSystem.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Sprite.h"
#include "Texture.h"
#include "SubTexture.h"

struct RenderData
{
	const int vertexCount = 4;

	glm::vec2 positions[4];
	glm::vec2 texCoords[4];

	unsigned int vao;
	VertexBuffer* vb = nullptr;
	VertexBufferLayout layout;
	VertexArray va;
	IndexBuffer* ib = nullptr;
	Shader* shader = nullptr;

	void Init()
	{
		positions[0] = { -0.5f, -0.5f };
		positions[1] = {  0.5f, -0.5f };
		positions[2] = {  0.5f,  0.5f };
		positions[3] = { -0.5f,  0.5f };
		
		texCoords[0] = { 0.0f, 0.0f };
		texCoords[1] = { 1.0f, 0.0f };
		texCoords[2] = { 1.0f, 1.0f };
		texCoords[3] = { 0.0f, 1.0f };
		
		unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
		};

		GLCall(glGenVertexArrays(1, &vao));
		GLCall(glBindVertexArray(vao));

		float pos[(2 + 2) * 4];
		for (int i = 0; i < vertexCount; i++)
		{
			pos[i * vertexCount + 0] = positions[i].x;
			pos[i * vertexCount + 1] = positions[i].y;
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
		va.AddBuffer(*vb, layout);
	}

};

class Renderer 
{
private:
	Camera* m_Camera;
	RenderData data;

	//blank texture (figure this out later)
	//u can definitely just pass in the buffer with color, not having to pass texture? or just create blank texutre internally? ?? 
	Texture* blank = new Texture("src/res/textures/Blank.png");
public:
	void DrawQuad(glm::vec4 color, glm::vec2 position, glm::vec2 scale);
	void DrawQuad(Texture& texture, glm::vec2 position);
	void DrawQuad(SubTexture& texture, glm::vec2 position);

	Renderer(Camera *camera);
	void DrawSprite(Sprite *m_Sprite);
	void DrawParticles(const std::vector<Particle>& particles);
	void Clear() const; 
};