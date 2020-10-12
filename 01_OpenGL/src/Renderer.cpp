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

void Renderer::DrawCube(Texture& texture, glm::vec3 position, float rotation, float xAxes, float yAxes, float zAxes, glm::vec3* lightPos, float ambientStrength, const glm::vec3& lightColor, float Shininess, float SpecularStrength)
{
	texture.Bind();

	glm::vec2 scale = glm::vec2(1.0f, 1.0f);

	glm::mat4 transform = glm::translate(glm::mat4(1.0f), { position.x, position.y, position.z })
		* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { xAxes, yAxes, zAxes })
		* glm::scale(glm::mat4(1.0f), { scale.x, scale.y, 1.0f });

	data.vb->Bind();
	data.va.Bind();
	data.ib->Bind();
	data.shaders["basic"]->Bind();
	data.shaders["basic"]->SetUniformMat4f("u_ViewProjection", m_Camera->GetProjection());
	data.shaders["basic"]->SetUniformMat4f("u_Model", transform);
	data.shaders["basic"]->SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
	data.shaders["basic"]->SetUniform4f("u_ColorElement", 1.0f, 1.0f, 1.0f, 1.0f);
	data.shaders["basic"]->SetUniform3f("u_CameraPos", m_Camera->GetPosition().x, m_Camera->GetPosition().y, m_Camera->GetPosition().z);
	//uniforms for testing
	//sending all the "lightPos" info into frangment
	int iter = 0;
	for (int i = 0; i < 2; i++)
	{
		std::string u_name = "u_lightPos" + std::to_string(i);
		data.shaders["basic"]->SetUniform3f(u_name, lightPos[i].x, lightPos[i].y, lightPos[i].z);
	}

	data.shaders["basic"]->SetUniform1f("u_SpecularStrength", SpecularStrength);
	data.shaders["basic"]->SetUniform1f("u_AmbientStrength", ambientStrength);
	data.shaders["basic"]->SetUniform3f("u_lightColor", lightColor.r, lightColor.g, lightColor.b);
	data.shaders["basic"]->SetUniform1f("u_Shininess", Shininess);
	GLCall(glDrawElements(GL_TRIANGLES, data.ib->GetCount(), GL_UNSIGNED_INT, nullptr));
	data.vb->Unbind();
	data.va.Unbind();
	data.ib->Unbind();
	data.shaders["basic"]->Unbind();
	texture.Unbind();

}

void Renderer::DrawCube(Texture& texture, glm::vec3 position, glm::vec3 scale, float rotation, float xAxes, float yAxes, float zAxes)
{
	texture.Bind();

	glm::mat4 transform = glm::translate(glm::mat4(1.0f), { position.x, position.y, position.z })
		* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { xAxes, yAxes, zAxes })
		* glm::scale(glm::mat4(1.0f), { scale.x, scale.y, scale.z });

	data.vb->Bind();
	data.va.Bind();
	data.ib->Bind();
	data.shaders["skyBox"]->Bind();
	data.shaders["skyBox"]->SetUniformMat4f("u_ViewProjection", m_Camera->GetProjection());
	data.shaders["skyBox"]->SetUniformMat4f("u_Model", transform);
	GLCall(glDrawElements(GL_TRIANGLES, data.ib->GetCount(), GL_UNSIGNED_INT, nullptr));
	data.vb->Unbind();
	data.va.Unbind();
	data.ib->Unbind();
	data.shaders["skyBox"]->Unbind();
	texture.Unbind();

}

void Renderer::DrawColor(const glm::vec4& color, glm::vec3 position, float rotation, float xAxes, float yAxes, float zAxes)
{
	glm::vec2 scale = glm::vec2(1.0f, 1.0f);

	glm::mat4 transform = glm::translate(glm::mat4(1.0f), { position.x, position.y, position.z })
		* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { xAxes, yAxes, zAxes })
		* glm::scale(glm::mat4(1.0f), { scale.x, scale.y, 1.0f });

	data.vb->Bind();
	data.va.Bind();
	data.ib->Bind();
	data.shaders["plainColor"]->Bind();
	data.shaders["plainColor"]->SetUniformMat4f("u_Projection", m_Camera->GetProjection());
	data.shaders["plainColor"]->SetUniformMat4f("u_View", m_Camera->GetView());
	data.shaders["plainColor"]->SetUniformMat4f("u_Model", transform);
	data.shaders["plainColor"]->SetUniform4f("u_Color", color.r, color.g, color.b, 1.0f);
	GLCall(glDrawElements(GL_TRIANGLES, data.ib->GetCount(), GL_UNSIGNED_INT, nullptr));
	data.vb->Unbind();
	data.va.Unbind();
	data.ib->Unbind();
	data.shaders["plainColor"]->Unbind();
}

void Renderer::DrawModel(Texture& diffuse, Texture& specular, Texture& normals, Texture& AO, Texture& roughness, glm::vec3 position, glm::vec3* lightPos, float ambientStrength, const glm::vec3& lightColor, float Shininess, Model model)
{
	for(int i = 0; i < model.meshes.size(); i++)
	{
		float rotation = 0.0f;
		glm::vec2 scale = glm::vec2(1.0f, 1.0f);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), { position.x, position.y, position.z })
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0, 0, 1 })
			* glm::scale(glm::mat4(1.0f), { scale.x, scale.y, 1.0f });

		model.meshes[i].vb->Bind();
		model.meshes[i].va->Bind();
		model.meshes[i].ib->Bind();
		data.shaders["basic"]->Bind();
		diffuse.Bind(0);
		data.shaders["basic"]->SetUniform1i("u_diffuseMap", 0);
		specular.Bind(1);
		data.shaders["basic"]->SetUniform1i("u_specularMap", 1);
		normals.Bind(2);
		data.shaders["basic"]->SetUniform1i("u_normalMap", 2);
		AO.Bind(3);
		data.shaders["basic"]->SetUniform1i("u_AO", 3);
		roughness.Bind(4);
		data.shaders["basic"]->SetUniform1i("u_roughness", 4);


		data.shaders["basic"]->SetUniformMat4f("u_Projection", m_Camera->GetProjection());
		data.shaders["basic"]->SetUniformMat4f("u_View", m_Camera->GetView());
		data.shaders["basic"]->SetUniformMat4f("u_Model", transform);
		data.shaders["basic"]->SetUniform3f("u_CameraPos", m_Camera->GetPosition().x, m_Camera->GetPosition().y, m_Camera->GetPosition().z);

		//sending all the "lightPos" info into frangment
		int iter = 0;
		for (int i = 0; i < 2; i++)
		{
			std::string u_name = "u_lightPos" + std::to_string(i);
			data.shaders["basic"]->SetUniform3f(u_name, lightPos[i].x, lightPos[i].y, lightPos[i].z);
		}

		//uniforms for testing
		data.shaders["basic"]->SetUniform1f("u_AmbientStrength", ambientStrength);
		data.shaders["basic"]->SetUniform3f("u_lightColor", lightColor.r, lightColor.g, lightColor.b);
		data.shaders["basic"]->SetUniform1f("u_Shininess", Shininess);
		GLCall(glDrawElements(GL_TRIANGLES, model.meshes[i].ib->GetCount(), GL_UNSIGNED_INT, nullptr));
		model.meshes[i].vb->Unbind();
		model.meshes[i].va->Unbind();
		model.meshes[i].ib->Unbind();
		data.shaders["basic"]->Unbind();
		diffuse.Unbind();
	}
}

void Renderer::Clear() const
{
	GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}
