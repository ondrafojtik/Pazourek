#include "Sprite.h"

Sprite::Sprite(float xPos, float yPos, float SpriteWidth, float SpriteHeight, const std::string TexturePath, glm::vec4 color, const std::string shaderPath) 
	: m_xPos(xPos), m_yPos(yPos), m_TexturePath(TexturePath), m_SpriteWidth(SpriteWidth), m_SpriteHeight(SpriteHeight), m_Color(color), m_colorElement(glm::vec4(1.0f)), m_Rotation(0.0f), m_Size(1.0f)
{

	float positions[] = {
		-0.5f, -0.5f, 0.0f, 0.0f,
		 0.5f, -0.5f, 1.0f, 0.0f,
		 0.5f,  0.5f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 1.0f,
	};

	unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
	};
	
	//VAO
	unsigned int m_VAO;
	GLCall(glGenVertexArrays(1, &m_VAO));
	GLCall(glBindVertexArray(m_VAO));

	//VB
	m_VB = new VertexBuffer(positions, 4 * 4 * sizeof(float));

	//Layout
	m_Layout.Push<float>(2);
	m_Layout.Push<float>(2);

	//VA
	m_VA.AddBuffer(*m_VB, m_Layout);

	//IB
	m_IB = new IndexBuffer(indices, 6);

	//Shader
	m_Shader = new Shader(shaderPath);
	m_Shader->Bind();
	
	//Texture
	m_Texture = new Texture(TexturePath);
	m_Texture->Bind();

	m_originalSize = { m_SpriteWidth, m_SpriteHeight };

	m_VA.Unbind();
	m_VB->Unbind();
	m_IB->Unbind();
	m_Shader->Unbind();
	m_Texture->Unbind();

}

Sprite::~Sprite()
{
	delete m_IB;
	delete m_VB;
	delete m_Shader;
	delete m_Texture;
}

void Sprite::MoveSprite(float xPos, float yPos)
{
	m_xPos = xPos;
	m_yPos = yPos;
	
}

void Sprite::MoveSpriteBy(float xPos, float yPos)
{
	m_xPos = m_xPos + xPos;
	m_yPos = m_yPos + yPos;

}

void Sprite::RotateSprite(float angle)
{
	this->m_Rotation = angle;
}

void Sprite::SetColorElement(glm::vec4 color)
{
	this->m_colorElement = color;
}

void Sprite::SetPivot(unsigned int type)
{
	float verticalDif;
	float horizontalDif;

	switch (type)
	{
		case DEFAULT:
		{
			verticalDif = 0;
			horizontalDif = 0;
			break;
		}
		case CENTER: 
		{
			verticalDif = 0;
			horizontalDif = 0;
			break;
		}
		case BOTTOM_LEFT:		
		{
			verticalDif = 0.5f;
			horizontalDif = 0.5f;
			break;
		}
		case BOTTOM_RIGHT:
		{
			verticalDif = -0.5;
			horizontalDif = 0.5f;
			break;
		}
		case TOP_RIGHT:			
		{
			verticalDif = -0.5f;
			horizontalDif = -0.5;
			break;
		}
		case TOP_LEFT:		
		{
			verticalDif = 0.5f;
			horizontalDif = -0.5f;
			break;
		}
		default:
		{
			verticalDif = 0.0f;
			horizontalDif = 0.0f;
			break;
		}
		
	}

	float positions[] = {
		-0.5f + verticalDif, -0.5f + horizontalDif, 0.0f, 0.0f,
		 0.5f + verticalDif, -0.5f + horizontalDif, 1.0f, 0.0f,
		 0.5f + verticalDif,  0.5f + horizontalDif, 1.0f, 1.0f,
		-0.5f + verticalDif,  0.5f + horizontalDif, 0.0f, 1.0f,
	};

	m_VB = new VertexBuffer(positions, 4 * 4 * sizeof(float));
	m_VA.AddBuffer(*m_VB, m_Layout);
}

void Sprite::OnRender()
{
	m_Texture->Bind();

	glm::mat4 transform = glm::translate(glm::mat4(1.0f), {m_xPos, m_yPos, 0.0f })
		* glm::rotate(glm::mat4(1.0f), m_Rotation, { 0.0f, 0.0f, 1.0f })
		* glm::scale(glm::mat4(1.0f), { m_SpriteWidth, m_SpriteHeight, 1.0f });
	
	m_Shader->SetUniformMat4f("u_Transform", transform);
	m_Shader->SetUniform4f("u_Color", m_Color.x, m_Color.y, m_Color.z, m_Color.a);
	m_Shader->SetUniform4f("u_ColorElement", m_colorElement.x, m_colorElement.y, m_colorElement.z, m_colorElement.a);
	m_VA.Bind();
	m_IB->Bind();
	GLCall(glDrawElements(GL_TRIANGLES, m_IB->GetCount(), GL_UNSIGNED_INT, nullptr));
	m_VA.Unbind();
	m_IB->Unbind();
	m_Shader->Unbind();
	}
