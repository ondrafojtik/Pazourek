#include "Animation.h"

Animation::Animation(const std::string& path, int numberOfFrames)
	: m_CurrentFrame(0), m_NumberOfFrames(numberOfFrames), m_InputPath(path)
{}

Animation::~Animation()
{

}

void Animation::RenderNext()
{
	//generace spravneho jmeno
	if (m_CurrentFrame == m_NumberOfFrames)
	{
		m_CurrentFrame = 0;
	}
	ss_FilePath << m_InputPath << m_CurrentFrame << ".tga";
	m_CurrentFrame++;
	ss_FilePath >> m_FilePath;
	std::cout << m_FilePath << std::endl;
	//render framu
	//Texture* texture = new Texture(m_FilePath.c_str()); //upravit s tim, kdy smazu z textury m_NumberOfFrames
	this->texture = new Texture(m_FilePath.c_str());
	texture->Bind();
	//delete frame
	//texture.Unbind();
	//texture.~Texture();
	ss_FilePath = std::stringstream();
}

void Animation::TextureClear()
{
	this->texture->~Texture();
}

