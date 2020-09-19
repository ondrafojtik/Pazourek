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
	//v_position = vec4(u_Transform * position).xyz;
	v_position = vec3(u_Transform * position);
	v_normal = vec3(u_Transform * vec4(normal, 1.0f));
	//v_normal = transpose(inverse(mat3(u_Transform))) * normal;
	//v_normal = mat3(transpose(inverse(u_Transform))) * normal;
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
uniform vec3 u_ViewPos;

void main()
{
	//ambient
	vec3 ambient = vec3(0.1f, 0.1f, 0.1f);
	vec3 norm = normalize(v_normal);
	vec3 lightDir = normalize(u_lightPos0 - v_position);
	//diffuse
	vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
	float diff = clamp(dot(norm, lightDir), 0.0f, 1.0f);
	vec3 diffuse = diff * lightColor;
	//specular
	float specularStrength = 0.5f;
	vec3 viewDir = normalize(u_ViewPos - v_normal);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = lightColor * specularStrength * spec;

	vec3 result = (ambient + diffuse + specular);

	//vec3 lightVector = normalize(u_lightPos0 - v_position);
	//float dot_product = max(dot(lightVector, normalize(v_normal)), 0.0);
	//vec4 diffuse = dot_product * vec4( 0.385, 0.647, 0.812, 1.0);
	//vec4 ambient = vec4( 0.1, 0.1, 0.1, 1.0);
	//vec4 final = ambient + diffuse;

	vec4 texColor = texture(u_Texture, v_TexCoord) * 1.0;
	color = texture(u_Texture, v_TexCoord * 1) * u_Color;
	color = vec4(color.x, color.y, color.z, color.a) * u_ColorElement * vec4(result, 1.0f);


	//color = vec4(v_position, 0.5f)
	//	* (vec4(ambientLight, 1) + vec4(diffuseFinal, 1.0f));

}