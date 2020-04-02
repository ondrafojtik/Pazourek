#pragma once

#include <iostream>

#include "GL/glew.h"

#include "Sprite.h"
#include "Camera.h"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer 
{
private:
	Camera* m_Camera;
public:
	Renderer(Camera *camera);
	//void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
	void DrawSprite(Sprite *m_Sprite);
	void Clear() const; 
};