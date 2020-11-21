#include "Renderer.h"


//linked to GLCall, might have to deal with later
void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << ")" << function << " " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}

Renderer::Renderer(Camera *camera) : m_Camera(camera) 
{
	data.Init();
}

//skyBox
void Renderer::DrawCube(Texture& texture, glm::vec3 position, glm::vec3 scale,
                        float rotation, float xAxes, float yAxes, float zAxes)
{

    glStencilFunc(GL_ALWAYS, 0, GL_REPLACE);

    texture.Bind();

	glm::mat4 transform = glm::translate(glm::mat4(1.0f), { position.x, position.y, position.z })
		* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { xAxes, yAxes, zAxes })
		* glm::scale(glm::mat4(1.0f), { scale.x, scale.y, scale.z });

	data.vb->Bind();
	data.va.Bind();
	data.ib->Bind();
	data.shaders["skyBox"]->Bind();
	data.shaders["skyBox"]->SetUniformMat4f("u_Projection", m_Camera->GetProjection());
	data.shaders["skyBox"]->SetUniformMat4f("u_View", m_Camera->GetView());
	data.shaders["skyBox"]->SetUniformMat4f("u_Model", transform);
	GLCall(glDrawElements(GL_TRIANGLES, data.ib->GetCount(), GL_UNSIGNED_INT, nullptr));
	data.vb->Unbind();
	data.va.Unbind();
	data.ib->Unbind();
	data.shaders["skyBox"]->Unbind();
	texture.Unbind();

}

void Renderer::DrawLight(Light& light)
{
    glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
    float rotation = 0.0f;
    
	glm::mat4 transform =
        glm::translate(glm::mat4(1.0f), light.position)
		* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 1.0f, 0.0f, 0.0f })
		* glm::scale(glm::mat4(1.0f), { scale.x, scale.y, scale.z });


    Shader* shader = data.shaders["plainColor"];
    
    shader->Bind();
	data.va.Bind();
	data.ib->Bind();
	shader->Bind();
	shader->SetUniformMat4f("u_Projection", m_Camera->GetProjection());
	shader->SetUniformMat4f("u_View", m_Camera->GetView());
	shader->SetUniformMat4f("u_Model", transform);
	shader->SetUniform4f("u_Color", light.color.r, light.color.g, light.color.b, 1.0f);
    GLCall(glDrawElements(GL_TRIANGLES, data.ib->GetCount(), GL_UNSIGNED_INT, nullptr));
	data.vb->Unbind();
	data.va.Unbind();
	data.ib->Unbind();
	shader->Unbind();
}

void Renderer::DrawColor(const glm::vec4& color, glm::vec3 position,
                         float rotation, float xAxes, float yAxes, float zAxes)
{
	glm::vec3 scale = glm::vec3(0.2f, 0.2f, 0.2f);

	glm::mat4 transform =
        glm::translate(glm::mat4(1.0f), { position.x, position.y, position.z })
		* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { xAxes, yAxes, zAxes })
		* glm::scale(glm::mat4(1.0f), { scale.x, scale.y, scale.z });


    Shader* shader = data.shaders["plainColor"];
    
    shader->Bind();
	data.va.Bind();
	data.ib->Bind();
	shader->Bind();
	shader->SetUniformMat4f("u_Projection", m_Camera->GetProjection());
	shader->SetUniformMat4f("u_View", m_Camera->GetView());
	shader->SetUniformMat4f("u_Model", transform);
	shader->SetUniform4f("u_Color", color.r, color.g, color.b, 1.0f);
	GLCall(glDrawElements(GL_TRIANGLES, data.ib->GetCount(), GL_UNSIGNED_INT, nullptr));
	data.vb->Unbind();
	data.va.Unbind();
	data.ib->Unbind();
	shader->Unbind();
}

//model
void Renderer::DrawModel(Texture& diffuse, Texture& specular, Texture& normals,
                         Texture& AO, Texture& roughness, glm::vec3 position,
                         Light* lights, float ambientStrength,
                         float Shininess, Model model)
{
	Shader* shader = data.shaders["basic"];
	shader->Bind();
  
	float rotation = 0.0f;
	glm::vec2 scale = glm::vec2(1.0f, 1.0f);

	glm::mat4 transform =
		glm::translate(glm::mat4(1.0f), { position.x, position.y, position.z })
		* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0, 0, 1 })
		* glm::scale(glm::mat4(1.0f), { scale.x, scale.y, 1.0f });
    //sending all the "lightPos" info into frangment

    for (int i = 0; i < 2; i++)
    {
        std::string u_name = "lights_out[" + std::to_string(i) + "].position";
        shader->SetUniform3fv(u_name, lights[i].position);
        u_name = "lights_out[" + std::to_string(i) + "].color";
        shader->SetUniform3fv(u_name, lights[i].color);
        //u_name = "lights_out[" + std::to_string(i) + "].type";
        //shader->SetUniform1f(u_name, lights[i].type);
        //u_name = "lights_out[" + std::to_string(i) + "].cutoff";
        //shader->SetUniform1f(u_name, glm::cos(glm::radians(lights[i].cutoff)));
        u_name = "lights_out[" + std::to_string(i) + "].info";
        shader->SetUniform3f(u_name, lights[i].type,
                             glm::cos(glm::radians(lights[i].cutoff)), 0.0f);
        u_name = "lights_out[" + std::to_string(i) + "].lightDir";
        shader->SetUniform3fv(u_name, lights[i].lightDir);

    }
	shader->SetUniformMat4f("u_Projection", m_Camera->GetProjection());
	shader->SetUniformMat4f("u_View", m_Camera->GetView());
	shader->SetUniformMat4f("u_Model", transform);
	shader->SetUniform3f("u_CameraPos", m_Camera->GetPosition().x,
		m_Camera->GetPosition().y, m_Camera->GetPosition().z);
	shader->SetUniform1f("u_AmbientStrength", ambientStrength);
	shader->SetUniform1f("u_Shininess", Shininess);
	
	diffuse.Bind(0);
	shader->SetUniform1i("u_diffuseMap", 0);
	specular.Bind(1);
	shader->SetUniform1i("u_specularMap", 1);
	normals.Bind(2);
	shader->SetUniform1i("u_normalMap", 2);
	AO.Bind(3);
	shader->SetUniform1i("u_AO", 3);
	roughness.Bind(4);
	shader->SetUniform1i("u_roughness", 4);

    for(int i = 0; i < model.meshes.size(); i++)
	{
		        
        model.meshes[i].vb->Bind();
		model.meshes[i].va->Bind();
		model.meshes[i].ib->Bind();
	    
		GLCall(glDrawElements(GL_TRIANGLES, model.meshes[i].ib->GetCount(), GL_UNSIGNED_INT, nullptr));
		model.meshes[i].vb->Unbind();
		model.meshes[i].va->Unbind();
		model.meshes[i].ib->Unbind();
		
	}
	shader->Unbind();
}

// scrap
void Renderer::DrawMap(const RandomMap& map, glm::vec3 position)
{
    
    glStencilFunc(GL_ALWAYS, 1, 0xFF);

    float rotation = 0.0f;
	glm::vec3 scale = { 20.0f, map.scale, 20.0f };

	glm::mat4 transform =
        glm::translate(glm::mat4(1.0f), { position.x, position.y, position.z })
		* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0, 1, 0 })
		* glm::scale(glm::mat4(1.0f), { scale.x, scale.y, scale.z });

    map.vb->Bind();
	map.va->Bind();
	map.ib->Bind();
	data.shaders["procedural"]->Bind();
	data.shaders["procedural"]->SetUniformMat4f("u_Projection", m_Camera->GetProjection());
	data.shaders["procedural"]->SetUniformMat4f("u_View", m_Camera->GetView());
	data.shaders["procedural"]->SetUniformMat4f("u_Model", transform);
	data.shaders["procedural"]->SetUniform4f("u_Color", 0.1f, 0.5f, 0.05f, 1.0f);
	GLCall(glDrawElements(GL_TRIANGLES, map.ib->GetCount(), GL_UNSIGNED_INT, nullptr));
	map.vb->Unbind();
	map.va->Unbind();
	map.ib->Unbind();
	data.shaders["plainColor"]->Unbind();    

}

void Renderer::DrawLine(glm::vec3 p1, glm::vec3 p2)
{
	float line_vertex[] =
	{
		p1.x, p1.y, p1.z, 1.0f, 1.0f, 1.0f,
		p2.x, p2.y, p2.z, 1.0f, 1.0f, 1.0f,
	};

	unsigned int indices[] =
	{
		0, 1,
	};

	glm::mat4 transform = glm::mat4(1.0f);

	VertexBuffer* vb = new VertexBuffer(line_vertex, sizeof(line_vertex));
	IndexBuffer* ib = new IndexBuffer(indices, 2);
	VertexArray* va = new VertexArray();
	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(3);
	va->AddBuffer(*vb, layout);

	vb->Bind();
	va->Bind();
	ib->Bind();
	data.shaders["plainColor"]->Bind();
	data.shaders["plainColor"]->SetUniformMat4f("u_Projection", m_Camera->GetProjection());
	data.shaders["plainColor"]->SetUniformMat4f("u_View", m_Camera->GetView());
	data.shaders["plainColor"]->SetUniformMat4f("u_Model", transform);
	data.shaders["plainColor"]->SetUniform4f("u_Color", 0.1f, 0.9f, 0.05f, 1.0f);
	glVertexPointer(2, GL_FLOAT, 0, line_vertex);
	glLineWidth(5);
	GLCall(glDrawElements(GL_LINES, ib->GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear() const
{
	GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));
}
