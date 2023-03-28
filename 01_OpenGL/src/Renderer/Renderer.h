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
#include "GUI/GUI.h"


struct Renderer
{
	Renderer(Camera *camera_);
	
	void Clear() const;
	void DrawColor(float x, float y);
	void DrawQuad(glm::vec3 bot_left, glm::vec3 top_right, glm::vec4 color);
	void DrawChar(FontSheet& font, char32_t character, glm::vec3 position, glm::vec3 color);
	void DrawText(FontSheet& font, std::string text, glm::vec3 position, glm::vec3 color);
	void DrawLine(glm::vec2 from, glm::vec2 to, glm::vec4 color);
	void DrawBorder(glm::vec3 top_left, glm::vec3 bot_right);
	void DrawGUI(PZ::GUI& gui, FontSheet& font);
	//////////////////////////////////////////////
	Camera* camera = nullptr;
	std::unordered_map<std::string, Shader*> shaders;

	unsigned int vao;
	VertexBuffer* vb = nullptr;
	VertexBufferLayout layout;
	VertexArray va;
	IndexBuffer* ib = nullptr;
	
};
