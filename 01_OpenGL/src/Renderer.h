#pragma once
#include "GL/glew.h"

#include <memory>

#include "Camera.h"
#include "ParticleSystem.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "SubTexture.h"
#include <unordered_map>

struct RenderData
{
	const int vertexCount = 4; 
	const int vertexInfo = 5;	//not "vertexCount, but how much info does 1 vertex carry (3 + 2) - you should make this more "normal"

	glm::vec3 positions[8];
	glm::vec2 texCoords[4];

	unsigned int vao;
	VertexBuffer* vb = nullptr;
	VertexBufferLayout layout;
	VertexArray va;
	IndexBuffer* ib = nullptr;
	//make this into some sorta std::unordered_map<std::string, Shader> or smth (and keep it here)
	//Shader* shader = nullptr;
	//Shader* shader_lightning = nullptr;
	std::unordered_map<std::string, Shader*> shaders;

	VertexBuffer* unchanged_vb = nullptr;
	VertexArray unchanged_va;

	void Init()
	{
		//side 1 (front)
		positions[0] = { -0.5f, -0.5f, 0.5f };
		positions[1] = {  0.5f, -0.5f, 0.5f };
		positions[2] = {  0.5f,  0.5f, 0.5f };
		positions[3] = { -0.5f,  0.5f, 0.5f };
		
		//side 2 (back)
		positions[4] = { -0.5f, -0.5f, -0.5f };
		positions[5] = {  0.5f, -0.5f, -0.5f };
		positions[6] = {  0.5f,  0.5f, -0.5f };
		positions[7] = { -0.5f,  0.5f, -0.5f };


		texCoords[0] = { 0.0f, 0.0f };
		texCoords[1] = { 1.0f, 0.0f };
		texCoords[2] = { 1.0f, 1.0f };
		texCoords[3] = { 0.0f, 1.0f };
		
		unsigned int indices[] = {
		0, 1, 2, //front
		2, 3, 0,
		1, 5, 6, //right
		6, 2, 1,
		4, 0, 3, //left
		3, 7, 4,
		3, 2, 6, //top
		6, 7, 3,
		0, 1, 5, //bottom
		5, 4, 0,
		};

		GLCall(glGenVertexArrays(1, &vao));
		GLCall(glBindVertexArray(vao));

		float pos[(3 + 2) * 4];
		for (int i = 0; i < vertexCount; i++)
		{
			pos[i * vertexInfo + 0] = positions[i].x;
			pos[i * vertexInfo + 1] = positions[i].y;
			pos[i * vertexInfo + 2] = positions[i].z;
			pos[i * vertexInfo + 3] = texCoords[i].x;
			pos[i * vertexInfo + 4] = texCoords[i].y;
		}

		vb = new VertexBuffer(positions, 4 * 8 * sizeof(float));
		unchanged_vb = new VertexBuffer(positions, 4 * 8 * sizeof(float));
		
		layout.Push<float>(3);
		//layout.Push<float>(2);

		unchanged_va.AddBuffer(*unchanged_vb, layout);

		va.AddBuffer(*vb, layout);
		ib = new IndexBuffer(indices, 24);

		shaders["basic"] = new Shader("src/res/shaders/Basic.shader");
		shaders["lightning"] = new Shader("src/res/shaders/basic_lightning.shader");
	}

	void RefreshData()
	{
		float pos[(3 + 2) * 4];
		for (int i = 0; i < vertexCount; i++)
		{
			pos[i * vertexInfo + 0] = positions[i].x;
			pos[i * vertexInfo + 1] = positions[i].y;
			pos[i * vertexInfo + 2] = positions[i].z;
			pos[i * vertexInfo + 3] = texCoords[i].x;
			pos[i * vertexInfo + 4] = texCoords[i].y;
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
	Texture* grid = new Texture("src/res/textures/grid.png");
public:
	void DrawQuad(glm::vec4 color, glm::vec2 position, glm::vec2 scale, float rotation);
	void DrawGrid(glm::vec4 color, glm::vec2 position);
	void DrawQuad(Texture& texture, glm::vec2 position, float rotation);
	void DrawQuad(Texture& texture, glm::vec2 position, glm::vec2 size);
	void DrawQuad(SubTexture& texture, glm::vec2 position, float rotation);
	//this is what lightning is as of now
	void DrawLighning(glm::vec4 color, glm::vec2 position, glm::vec2 scale);

	Renderer(Camera *camera);
	void Clear() const; 
};