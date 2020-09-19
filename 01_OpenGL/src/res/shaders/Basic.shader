#shader vertex
#version 330 core

layout(location = 0) in vec4 position; //meaning -0.5f, .. (vertexBuff more or less) 
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

out vec2 v_TexCoord;
out vec4 v_colorElement;
out vec3 v_position;
out vec3 v_normal;

uniform mat4 u_Proj; //ModelViewProjection matrix
uniform mat4 u_Transform;


void main()
{
	gl_Position = (u_Proj * u_Transform * position); //u_Proj * u_Transform * position;
	v_TexCoord = texCoord;
	v_position = vec4(u_Transform * position).xyz;
	v_normal = mat3(u_Transform) * normal;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in vec4 v_colorElement;
in vec3 v_position;
in vec3 v_normal;

uniform sampler2D u_Texture;
uniform vec4 u_Color;
uniform vec4 u_ColorElement;
uniform vec3 u_lightPos0;

void main()
{
	//ambient
	vec3 ambientLight = vec3(0.1f, 0.1f, 0.1f);

	//diffuse
	vec3 posToLightNormDir = normalize(v_position - u_lightPos0);
	vec3 diffuseColor = vec3(1.0f, 1.0f, 1.0f);
	float diffuse = clamp(dot(posToLightNormDir, v_normal), 0, 1);
	vec3 diffuseFinal = diffuseColor * diffuse;

	vec4 texColor = texture(u_Texture, v_TexCoord) * 1.0;
	color = texture(u_Texture, v_TexCoord * 1) * u_Color;
	color = vec4(color.x, color.y, color.z, color.a) * u_ColorElement
		* (vec4(ambientLight, 1) + vec4(diffuseFinal, 1.0f));
	
	
	//color = vec4(v_position, 0.5f)
	//	* (vec4(ambientLight, 1) + vec4(diffuseFinal, 1.0f));
	
}