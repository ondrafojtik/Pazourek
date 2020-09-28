#include <vector>

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Texture.h"

#include "glm/vec3.hpp"
#include "glm/vec2.hpp"

//#define MAX_VERTEX_COUNT 100

struct Vertex
{
	glm::vec3 position;
	glm::vec2 texCoord;
	glm::vec3 normal;
};

struct Mesh
{
	const int vertexCount = 24;
	const int vertexInfo = 3 + 2 + 3;

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	unsigned int vao;
	VertexBuffer* vb = nullptr;
	VertexBufferLayout layout;
	VertexArray va;
	IndexBuffer* ib = nullptr;

	//Mesh(std::vector<Vertex> __vertices, std::vector<unsigned int> __indices, std::vector<Texture> __textures)
	//: vertices(__vertices), indices(__indices), textures(__textures)
	Mesh()
	{
		setupMesh();
	}

	void setupMesh()
	{
		glm::vec3 positions[24];
		glm::vec2 texCoords[24];
		glm::vec3 normal[24];

		positions[0] = { -0.5f, -0.5f, -0.5f };
		positions[1] = { 0.5f, -0.5f, -0.5f };
		positions[2] = { 0.5f,  0.5f, -0.5f };
		positions[3] = { -0.5f,  0.5f, -0.5f };

		texCoords[0] = { 0.25f, 0.33333f };
		texCoords[1] = { 0.5f, 0.33333f };
		texCoords[2] = { 0.5f, 0.66666f };
		texCoords[3] = { 0.25f, 0.66666f };

		normal[0] = { 0.0f, 0.0f, -1.0f };
		normal[1] = { 0.0f, 0.0f, -1.0f };
		normal[2] = { 0.0f, 0.0f, -1.0f };
		normal[3] = { 0.0f, 0.0f, -1.0f };

		//side 2 (right)
		positions[4] = { 0.5f, -0.5f, -0.5f };
		positions[5] = { 0.5f, -0.5f,  0.5f };
		positions[6] = { 0.5f,  0.5f,  0.5f };
		positions[7] = { 0.5f,  0.5f, -0.5f };

		texCoords[4] = { 0.5f, 0.33333f };
		texCoords[5] = { 0.75f, 0.33333f };
		texCoords[6] = { 0.75f, 0.66666f };
		texCoords[7] = { 0.5f, 0.66666f };

		normal[4] = { 1.0f, 0.0f, 0.0f };
		normal[5] = { 1.0f, 0.0f, 0.0f };
		normal[6] = { 1.0f, 0.0f, 0.0f };
		normal[7] = { 1.0f, 0.0f, 0.0f };

		//side 3 (back)
		positions[8] = { 0.5f, -0.5f, 0.5f };
		positions[9] = { -0.5f, -0.5f, 0.5f };
		positions[10] = { -0.5f,  0.5f, 0.5f };
		positions[11] = { 0.5f,  0.5f, 0.5f };

		texCoords[8] = { 0.75f, 0.33333f };
		texCoords[9] = { 1.0f, 0.33333f };
		texCoords[10] = { 1.0f, 0.66666f };
		texCoords[11] = { 0.75f, 0.66666f };

		normal[8] = { 0.0f, 0.0f, 1.0f };
		normal[9] = { 0.0f, 0.0f, 1.0f };
		normal[10] = { 0.0f, 0.0f, 1.0f };
		normal[11] = { 0.0f, 0.0f, 1.0f };

		//side 4 (left)
		positions[12] = { -0.5f, -0.5f,  0.5f };
		positions[13] = { -0.5f, -0.5f, -0.5f };
		positions[14] = { -0.5f,  0.5f, -0.5f };
		positions[15] = { -0.5f,  0.5f,  0.5f };

		texCoords[12] = { 0.0f, 0.33333f };
		texCoords[13] = { 0.25f, 0.33333f };
		texCoords[14] = { 0.25f, 0.66666f };
		texCoords[15] = { 0.0f, 0.66666f };

		normal[12] = { -1.0f, 0.0f, 0.0f };
		normal[13] = { -1.0f, 0.0f, 0.0f };
		normal[14] = { -1.0f, 0.0f, 0.0f };
		normal[15] = { -1.0f, 0.0f, 0.0f };

		//side 5 (bottom)
		positions[16] = { -0.5f, -0.5f, -0.5f };
		positions[17] = { 0.5f, -0.5f, -0.5f };
		positions[18] = { 0.5f, -0.5f,  0.5f };
		positions[19] = { -0.5f, -0.5f,  0.5f };

		texCoords[16] = { 0.25f, 0.33333f };
		texCoords[17] = { 0.5f, 0.33333f };
		texCoords[18] = { 0.5f, 0.0f };
		texCoords[19] = { 0.25f, 0.0f };

		normal[16] = { 0.0f, -1.0f, 0.0f };
		normal[17] = { 0.0f, -1.0f, 0.0f };
		normal[18] = { 0.0f, -1.0f, 0.0f };
		normal[19] = { 0.0f, -1.0f, 0.0f };

		//side 5 (top)
		positions[20] = { -0.5f, 0.5f, -0.5f };
		positions[21] = { 0.5f, 0.5f, -0.5f };
		positions[22] = { 0.5f, 0.5f,  0.5f };
		positions[23] = { -0.5f, 0.5f,  0.5f };

		texCoords[20] = { 0.25f, 0.66666f };
		texCoords[21] = { 0.5f, 0.66666f };
		texCoords[22] = { 0.5f, 1.0f };
		texCoords[23] = { 0.25f, 1.0f };

		normal[20] = { 0.0f, 1.0f, 0.0f };
		normal[21] = { 0.0f, 1.0f, 0.0f };
		normal[22] = { 0.0f, 1.0f, 0.0f };
		normal[23] = { 0.0f, 1.0f, 0.0f };

		unsigned int _indices[] = {
		0, 1, 2, //front
		2, 3, 0,
		4, 5, 6, //right
		6, 7, 4,
		8, 9, 10, //back
		10, 11, 8,
		12, 13, 14, //left
		14, 15, 12,
		16, 17, 18, //bottom
		18, 19, 16,
		20, 21, 22, //top
		22, 23, 20,
		};
		for (unsigned int value : _indices)
			indices.push_back(value);

		GLCall(glGenVertexArrays(1, &vao));
		GLCall(glBindVertexArray(vao));
		//position, texCoords, normal
		float* pos = new float[(sizeof(Vertex) / sizeof(float)) * vertexCount]; //it seems it CAN be dynamic! 
		//float pos[sizeof(Vertex) * MAX_VERTEX_COUNT];
		for (int i = 0; i < vertexCount; i++)
		{
			pos[i * vertexInfo + 0] = positions[i].x;
			pos[i * vertexInfo + 1] = positions[i].y;
			pos[i * vertexInfo + 2] = positions[i].z;
			pos[i * vertexInfo + 3] = texCoords[i].x;
			pos[i * vertexInfo + 4] = texCoords[i].y;
			pos[i * vertexInfo + 5] = normal[i].x;
			pos[i * vertexInfo + 6] = normal[i].y;
			pos[i * vertexInfo + 7] = normal[i].z;
		}
		
		vb = new VertexBuffer(pos, vertexCount * (3 + 2 + 3) * sizeof(float)); //(pos, vertices.size() * sizeof(Vertex))
		layout.Push<float>(3);
		layout.Push<float>(2);
		layout.Push<float>(3);

		va.AddBuffer(*vb, layout);
		unsigned int* _data;
		_data = &_indices[0];
		ib = new IndexBuffer(_data, indices.size());
	}

	void Bind()
	{
		vb->Bind();
		va.Bind();
		ib->Bind();
	}

	void UnBind()
	{
		vb->Unbind();
		va.Unbind();
		ib->Unbind();
	}
	
	
};