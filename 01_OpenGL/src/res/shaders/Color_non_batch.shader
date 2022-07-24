#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;

uniform mat4 u_view;
uniform mat4 u_projection;

out vec4 v_Color;

void main()
{
	gl_Position = u_projection * u_view * position;
	v_Color = color;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec4 v_Color;

void main()
{
	color = v_Color;
	color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}