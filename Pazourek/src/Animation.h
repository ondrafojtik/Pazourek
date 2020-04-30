#pragma once

#include <string>
#include <sstream>
#include "Texture.h"

#include <iostream>

class Animation
{
private: 
	int m_CurrentFrame;
	int m_NumberOfFrames;
	std::stringstream ss_FilePath;
	std::string m_InputPath;
	
public:
	Texture* texture;
	std::string m_FilePath;

	Animation(const std::string& path, int numberOfFrames);
	~Animation();
	void RenderNext();
	void TextureClear();
};