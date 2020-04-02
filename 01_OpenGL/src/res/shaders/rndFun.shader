#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;
out vec4 v_colorElement;

uniform mat4 u_Proj; //ModelViewProjection matrix
uniform mat4 u_Transform;
uniform vec4 u_ColorElement; 

void main()
{
	gl_Position = gl_Position = u_Proj * u_Transform * position;
	v_TexCoord = texCoord;
	v_colorElement = u_ColorElement;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in vec4 v_colorElement;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
	vec4 texColor = texture(u_Texture, v_TexCoord) * 1.0;
	//color = texColor * (0.0, 0.0, 123.0, 1.0);
	color = texture(u_Texture, v_TexCoord * 1) * u_Color;
	color = color * v_colorElement * (v_TexCoord.x + 10.0f);
}