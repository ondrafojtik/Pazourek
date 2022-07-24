#pragma once

#include "stb-master\stb_image.h"

#include <iostream>
#include "GLcall.h"
#include <sstream>

struct OriginalTextureSize
{
	int width, height;
};

class Texture
{
private:
	unsigned int m_RendererID;
	int m_Width, m_Height, m_BPP;
	OriginalTextureSize m_OrignalSize;

public:

	unsigned char* m_LocalBuffer;
	Texture(const std::string& path);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	unsigned int GetTexID() { return m_RendererID; }
	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
	OriginalTextureSize GetOriginalSize() const { return m_OrignalSize; }
}; 
