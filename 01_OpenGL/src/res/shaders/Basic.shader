#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 tangent;
layout(location = 4) in vec3 bitangent;


out vec2 v_TexCoord;
out vec4 v_colorElement;
out vec3 v_position;
out vec3 v_normal;
out mat3 TBN;

out vec3 v_FragPos;
out mat4 v_Model;

out vec3 tangentLightPos;
out vec3 tangentViewPos;
out vec3 tangentFragPos;

uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Model;

uniform vec3 u_lightPos0;
uniform vec3 u_CameraPos;

void main()
{
    v_FragPos = vec3(u_Model * vec4(position, 1.0));
    v_TexCoord = texCoord;

    mat3 normalMatrix = transpose(inverse(mat3(u_Model)));
    vec3 T = normalize(normalMatrix * tangent);
    vec3 N = normalize(normalMatrix * normal);
    T = normalize(T - dot(T, N) * N);
    vec3 B = cross(N, T);

    mat3 TBN = transpose(mat3(T, B, N));
    tangentLightPos = TBN * u_lightPos0;
    tangentViewPos = TBN * u_CameraPos;
    tangentFragPos = TBN * v_FragPos;

    gl_Position = u_Projection * u_View * u_Model * vec4(position, 1.0);
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in vec4 v_colorElement;
in vec3 v_position;
in vec3 v_normal;

in vec3 v_FragPos;
in mat3 TBN;
in mat4 v_Model;

in vec3 tangentLightPos;
in vec3 tangentViewPos;
in vec3 tangentFragPos;

uniform sampler2D u_diffuseMap;
uniform sampler2D u_specularMap;

uniform sampler2D u_AO;
uniform sampler2D u_roughness;
uniform sampler2D u_normalMap;

uniform vec3 u_lightPos1;


//uniforms for testing 
uniform float u_AmbientStrength;
uniform vec3 u_lightColor;
uniform float u_Shininess;

vec3 t_diffuse = texture(u_diffuseMap, v_TexCoord).rgb;
vec3 t_specular = texture(u_specularMap, v_TexCoord).rgb;
vec3 t_normal = texture(u_normalMap, v_TexCoord).rgb;
float AO = texture(u_AO, v_TexCoord).r;
float specularStrength = texture(u_roughness, v_TexCoord).r;


//ligths still have to be put in here manually
#define LIGHT_COUNT = 2;

void main()
{
    // obtain normal from normal map in range [0,1]
    vec3 normal = texture(u_normalMap, v_TexCoord).rgb;
    // transform normal vector to range [-1,1]
    normal = normalize(normal * 2.0 - 1.0);  // this normal is in tangent space

    // get diffuse color
    vec3 a_color = texture(u_diffuseMap, v_TexCoord).rgb;
    // ambient
    vec3 ambient = 0.1 * a_color;
    // diffuse
    vec3 lightDir = normalize(tangentLightPos - tangentFragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * a_color * u_lightColor;
    // specular
    vec3 viewDir = normalize(tangentViewPos - tangentFragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);

    vec3 specular = t_specular * spec * u_lightColor;
    color = vec4(ambient + diffuse + specular, 1.0);
}