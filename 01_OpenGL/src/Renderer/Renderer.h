#pragma once
#include "GL/glew.h"

#include "Camera.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "FontSheet.h"
#include <map>

struct Renderer
{
	Renderer(Camera *camera_);
	
	void Clear() const;
	void DrawColor(float x, float y);
	void DrawChar(FontSheet& font, char32_t character, glm::vec3 position, glm::vec3 color);
	void DrawText(FontSheet& font, std::string text, glm::vec3 position, glm::vec3 color);
	//////////////////////////////////////////////
	Camera* camera = nullptr;
	std::unordered_map<std::string, Shader*> shaders;

	unsigned int vao;
	VertexBuffer* vb = nullptr;
	VertexBufferLayout layout;
	VertexArray va;
	IndexBuffer* ib = nullptr;
	
};
