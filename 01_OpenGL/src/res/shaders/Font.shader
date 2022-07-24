#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;
out vec3 v_position;

uniform mat4 u_Projection;
uniform mat4 u_View;

void main()
{
	gl_Position = u_Projection * u_View * vec4(position, 1.0);
	v_TexCoord = texCoord;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in vec3 v_position;

uniform sampler2D u_diffuseMap;
uniform vec4 u_Color;
vec4 diffuseMap = texture(u_diffuseMap, v_TexCoord);

void main()
{
	color = (diffuseMap * u_Color);
}