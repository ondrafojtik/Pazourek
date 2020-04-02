#pragma once

#include <string>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"

#include "GLcall.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Sprite	//xPos and yPos r both left bottom of the sprite
{
private:
	float m_xPos;
	float m_yPos;
	float m_SpriteWidth;
	float m_SpriteHeight;
	unsigned int m_VAO;
	VertexBuffer* m_VB;
	VertexBufferLayout m_Layout;
	std::string m_TexturePath;
	float m_Rotation;
	glm::vec4 m_colorElement;
	glm::vec4 m_Color;

public:
	VertexArray m_VA;		
	IndexBuffer *m_IB;		
	Shader *m_Shader;		
	Texture *m_Texture;

public:
	Sprite(float xPos, float yPos, float m_SpriteWidth, float SpriteHeight, const std::string TexturePath, const std::string shaderPath);
	Sprite(float xPos, float yPos, float m_SpriteWidth, float SpriteHeight, glm::vec4 color, const std::string shaderPath);
	~Sprite();

	void MoveSpriteBy(float xPos, float yPos);
	void MoveSprite(float xPos, float yPos);
	//angle in degrees
	void RotateSprite(float angle);
	void SetColorElement(glm::vec4 color);
	inline float GetXPos() { return m_xPos; }
	inline float GetYPos() { return m_yPos; }
	inline float GetWidth() { return m_SpriteWidth; }
	inline float GetHeight() { return m_SpriteHeight; }
	inline glm::vec3 GetPosition() { return glm::vec3(m_xPos, m_yPos, 1.0f); }
	inline float GetRotation() { return m_Rotation; }
	inline glm::vec4 GetColorElement() { return m_colorElement; }
	void SetColor(glm::vec4 color) { m_Color = color; }

	void OnRender();
	//inline VertexArray GetVA() { return m_VA; }
	//inline IndexBuffer GetIB() { return *m_IB; }
	//inline Shader GetShader() { return *m_Shader; }
	//inline Texture GetTexture() { return *m_Texture; }


};
