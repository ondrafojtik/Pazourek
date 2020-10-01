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
	Mesh(const std::vector<Vertex>& _vertices, const std::vector<unsigned int>& _indices, const std::vector<Texture>& _textures)
		: vertices(_vertices), indices(_indices), textures(_textures)
	{
		setupMesh();
	}


	//keeping the "positions, texCoords, .." here just to see if it works!
	void setupMesh()
	{
		int _vertexCount = vertices.size();


		GLCall(glGenVertexArrays(1, &vao));
		GLCall(glBindVertexArray(vao));
		//position, texCoords, normal
		float* pos = new float[(sizeof(Vertex) / sizeof(float)) * vertexCount]; //it seems it CAN be dynamic! 
		std::cout << "size: " << sizeof(pos) << std::endl;
		//float pos[sizeof(Vertex) * MAX_VERTEX_COUNT];
	
		for (int i = 0; i < _vertexCount; i++)
		{
			pos[i * vertexInfo + 0] = vertices[i].position.x;
			pos[i * vertexInfo + 1] = vertices[i].position.y;
			pos[i * vertexInfo + 2] = vertices[i].position.z;
			pos[i * vertexInfo + 3] = vertices[i].texCoord.x;
			pos[i * vertexInfo + 4] = vertices[i].texCoord.y;
			pos[i * vertexInfo + 5] = vertices[i].normal.x;
			pos[i * vertexInfo + 6] = vertices[i].normal.y;
			pos[i * vertexInfo + 7] = vertices[i].normal.z;

		}
		
		vb = new VertexBuffer(pos, vertexCount * (3 + 2 + 3) * sizeof(float)); //(pos, vertices.size() * sizeof(Vertex))
		layout.Push<float>(3);
		layout.Push<float>(2);
		layout.Push<float>(3);

		va.AddBuffer(*vb, layout);
		unsigned int* _data;
		_data = &indices[0];
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