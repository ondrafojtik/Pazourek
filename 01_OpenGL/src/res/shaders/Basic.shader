#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

out vec2 v_TexCoord;
out vec4 v_colorElement;
out vec3 v_position;
out vec3 v_normal;

out vec3 testNormal;

out vec3 v_FragPos;

uniform mat4 u_ViewProjection;
uniform mat4 u_Model;

void main()
{
	gl_Position = u_ViewProjection * u_Model * vec4(position, 1.0);
	v_TexCoord = texCoord;
	
	v_FragPos = vec3(u_Model * vec4(position, 1.0f));
	v_normal = inverse(transpose(mat3(u_Model))) * normal;
	testNormal = normal;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in vec4 v_colorElement;
in vec3 v_position;
in vec3 v_normal;

in vec3 v_FragPos;
in vec3 testNormal;

uniform sampler2D u_diffuseMap;
uniform sampler2D u_specularMap;
//uniform sampler2D u_normalMap;
//uniform sampler2D u_roughtnessMap;

uniform vec4 u_Color;
uniform vec4 u_ColorElement;
uniform vec3 u_lightPos0;
uniform vec3 u_lightPos1;
uniform vec3 u_CameraPos;

//uniforms for testing 
uniform float u_AmbientStrength;
uniform float u_SpecularStrength;
uniform vec3 u_lightColor;
uniform float u_Shininess;

vec4 diffuseMap = texture(u_diffuseMap, v_TexCoord);
vec4 specularMap = texture(u_specularMap, v_TexCoord);
//vec4 normalMap = texture(u_normalMap, v_TexCoord);
//vec4 roughtnessMap = texture(u_roughtnessMap, v_TexCoord);


vec3 calculateLight(vec3 lightPos, vec3 lightColor)
{
	//ambient
	float ambientStrength = u_AmbientStrength;
	vec3 ambient = ambientStrength * lightColor * vec3(diffuseMap);

	//diffuse
	vec3 norm = normalize(v_normal);
	vec3 lightDir = normalize(lightPos - v_FragPos);
	float diffuseStregth = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diffuseStregth * lightColor * vec3(diffuseMap);

	//specular
	float specularStrength = u_SpecularStrength;
	vec3 viewDir = normalize(u_CameraPos - v_FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Shininess);
	vec3 specular = specularStrength * spec * lightColor * vec3(specularMap);

	//result
	vec3 result = (ambient + diffuse + specular);
	return result;
}

//ligths still have to be put in here manually

#define LIGHT_COUNT = 2;
void main()
{
	vec3 result = (calculateLight(u_lightPos0, u_lightColor) + calculateLight(u_lightPos1, vec3(1.0f, 1.0f, 1.0f))) / 2;

	color = texture(u_diffuseMap, v_TexCoord) * u_Color;
	color = vec4(result, 1.0f) * vec4(color.x, color.y, color.z, color.a) * u_ColorElement * vec4(result, 1.0f);
	//color = vec4(abs(testNormal), 1.0f);
	


}