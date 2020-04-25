#include "Sprite.h"

Sprite::Sprite(float xPos, float yPos, float SpriteWidth, float SpriteHeight, const std::string TexturePath, const std::string shaderPath) 
	: m_xPos(xPos), m_yPos(yPos), m_TexturePath(TexturePath), m_SpriteWidth(SpriteWidth), m_SpriteHeight(SpriteHeight), m_Color(glm::vec4(1.0f)), m_colorElement(glm::vec4(1.0f)), m_Rotation(0.0f), m_Size(1.0f)
{
	
	float positions[] = {
		m_xPos,					m_yPos,					0.0f, 0.0f,
		m_xPos + m_SpriteWidth, m_yPos,					1.0f, 0.0f,
		m_xPos + m_SpriteWidth, m_yPos + m_SpriteHeight, 1.0f, 1.0f,
		m_xPos,					m_yPos + m_SpriteHeight, 0.0f, 1.0f,
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

	m_VA.Unbind();
	m_VB->Unbind();
	m_IB->Unbind();
	m_Shader->Unbind();
	m_Texture->Unbind();

}

Sprite::Sprite(float xPos, float yPos, float SpriteWidth, float SpriteHeight, glm::vec4 color, const std::string shaderPath)
	: m_xPos(xPos), m_yPos(yPos), m_Color(color), m_SpriteWidth(SpriteWidth), m_SpriteHeight(SpriteHeight), m_colorElement(glm::vec4(1.0f)), m_Rotation(0.0f),
	m_Size(1.0f)
{
	
	float positions[] = {
		m_xPos,					m_yPos,					0.0f, 0.0f,
		m_xPos + m_SpriteWidth, m_yPos,					1.0f, 0.0f,
		m_xPos + m_SpriteWidth, m_yPos + m_SpriteHeight, 1.0f, 1.0f,
		m_xPos,					m_yPos + m_SpriteHeight, 0.0f, 1.0f,
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
	m_Texture = new Texture("src/res/textures/Blank.png");

	m_Texture->Bind();

	m_VA.Unbind();
	m_VB->Unbind();
	m_IB->Unbind();
	m_Shader->Unbind();
	m_Texture->Unbind();

}

Sprite::Sprite(float xPos, float yPos, std::string TexturePath, std::string shaderPath) 
	: m_xPos(xPos), m_yPos(yPos), m_TexturePath(TexturePath), m_SpriteWidth(0), m_SpriteHeight(0), m_Color(glm::vec4(1.0f)), m_colorElement(glm::vec4(1.0f)), m_Rotation(0.0f), m_Size(1.0f)
{

	m_Texture = new Texture(TexturePath);
	m_SpriteWidth = m_Texture->GetWidth();
	m_SpriteHeight = m_Texture->GetHeight();
	std::cout << m_SpriteWidth << " " << m_SpriteHeight << "\n";

	float positions[] = {
		m_xPos,					m_yPos,					0.0f, 0.0f,
		m_xPos + m_SpriteWidth, m_yPos,					1.0f, 0.0f,
		m_xPos + m_SpriteWidth, m_yPos + m_SpriteHeight, 1.0f, 1.0f,
		m_xPos,					m_yPos + m_SpriteHeight, 0.0f, 1.0f,
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
	m_Texture->Bind();

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
	
	float positions[] = {
		m_xPos,					m_yPos,					0.0f, 0.0f,
		m_xPos + m_SpriteWidth, m_yPos,					1.0f, 0.0f,
		m_xPos + m_SpriteWidth, m_yPos + m_SpriteHeight, 1.0f, 1.0f,
		m_xPos,					m_yPos + m_SpriteHeight, 0.0f, 1.0f,
	};

	m_VB = new VertexBuffer(positions, 4 * 4 * sizeof(float));
	m_VA.AddBuffer(*m_VB, m_Layout);
}

void Sprite::MoveSpriteBy(float xPos, float yPos)
{
	m_xPos = m_xPos + xPos;
	m_yPos = m_yPos + yPos;

	float positions[] = {
		m_xPos,					m_yPos,					 0.0f, 0.0f,
		m_xPos + m_SpriteWidth, m_yPos,					 1.0f, 0.0f,
		m_xPos + m_SpriteWidth, m_yPos + m_SpriteHeight, 1.0f, 1.0f,
		m_xPos,					m_yPos + m_SpriteHeight, 0.0f, 1.0f,
	};

	m_VB = new VertexBuffer(positions, 4 * 4 * sizeof(float));
	m_VA.AddBuffer(*m_VB, m_Layout);
}

void Sprite::RotateSprite(float angle)
{
	this->m_Rotation = angle;
}

void Sprite::SetColorElement(glm::vec4 color)
{
	this->m_colorElement = color;
}

void Sprite::OnRender()
{
	m_Texture->Bind();
	#if 1
	glm::mat4 transform = glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0.0f, 0.0f, 1.0f))
		* glm::translate(glm::mat4(1.0f), glm::vec3(
			0.0f,
			0.0f,
			0.0f)) 
		* glm::scale(glm::mat4(1.0f), { m_Size, m_Size, 1.0f});
#else
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), {
		0.0f,
		0.0f,
		0.0f })
		* glm::rotate(glm::mat4(1.0f), m_Rotation, { 0.0f, 0.0f, 1.0f });
#endif
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
