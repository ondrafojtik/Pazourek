#shader vertex
#version 330 core

layout(location = 0) in vec4 position; //meaning -0.5f, .. (vertexBuff more or less) 
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;
out vec4 v_colorElement;
out vec4 v_position;

uniform mat4 u_Proj; //ModelViewProjection matrix
uniform mat4 u_Transform;
uniform vec4 u_ColorElement;

void main()
{
	gl_Position = (u_Proj * u_Transform * position); //u_Proj * u_Transform * position;
	v_TexCoord = texCoord;
	v_colorElement = u_ColorElement;
	v_position = position + 0.5;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in vec4 v_colorElement;
in vec4 v_position;

uniform sampler2D u_Texture;
uniform vec4 u_Color;

void main()
{
	//vec4 texColor = texture(u_Texture, v_TexCoord) * 1.0;
	//color = texture(u_Texture, v_TexCoord * 1) * u_Color;
	//color = vec4(color.x, color.y, color.z, color.a) * v_colorElement;
	color = v_position;
	color.a = 0.5;
}