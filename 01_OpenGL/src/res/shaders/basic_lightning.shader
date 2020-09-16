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
	gl_Position = (u_Proj * u_Transform * position); //u_Proj * u_Transform * position;
	v_TexCoord = texCoord;
	v_colorElement = u_ColorElement;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in vec4 v_colorElement;

uniform sampler2D u_Texture;
uniform vec4 u_Color;

void main()
{
	vec4 texColor = texture(u_Texture, v_TexCoord) * 1.0;
	color = texture(u_Texture, v_TexCoord * 1) * u_Color;
	vec2 coords = v_TexCoord;
	coords.xy = coords.xy - 0.5;
	float distance_from_middle = length(coords);
	distance_from_middle = distance_from_middle + 0.5;
	//very strong
	//color = vec4(color.x, color.y, color.z, color.a * (1.0 - distance_from_middle)) * v_colorElement;
	//more realistic
	color = vec4(color.r, color.g, color.b, color.a * (pow(0.01, distance_from_middle) - 0.01)) * v_colorElement;// *vec4(5, 5, 5, 5);
	color.rgba *= 10;
	//this one is like if u were staring into light bulb XD
	//color = vec4(color.x, color.y, color.z, color.a * ((1.0 / distance_from_middle) - distance_from_middle)) * v_colorElement;

}
//for debuging purpouse
/*if (distance_from_middle > 0)
		color = vec4(0, 1, 0, 1) * v_colorElement;
	if (distance_from_middle > 0.95)
		color = vec4(1, 0, 0, 1) * v_colorElement;
	else
		color = vec4(0, 0, 1, 1) * v_colorElement;
	*/