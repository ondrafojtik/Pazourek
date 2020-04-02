#shader vertex
#version 330 core

layout(location = 0) in vec4 position;

out vec4 v_Position;
out vec4 v_colorElement;

uniform mat4 u_Proj; //ModelViewProjection matrix
uniform mat4 u_Transform;
uniform vec4 u_ColorElement;

void main()
{
	gl_Position = gl_Position = u_Proj * u_Transform * position;
	v_Position = position;
	v_colorElement = u_ColorElement;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec4 v_Position;
in vec4 v_colorElement;
uniform vec4 u_Color;

void main()
{

	color = vec4(0.5 * v_colorElement.x,
		(((v_Position.x - 1280) / 1280) * 0.5 + 0.5) * v_colorElement.y,
		((v_Position.y - 720) / 720) * 0.5 + 0.5,
		1.0 * 0.5 + 0.5) * v_colorElement * u_Color;

	//color = vec4(	0.5, 
	//				((v_Position.x - 1280) / 1280) * 0.5 + 0.5,
	//				((v_Position.y - 720) / 720) * 0.5 + 0.5,
	//				1.0 * 0.5 + 0.5);
}