#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 tangent;
layout(location = 4) in vec3 bitangent;


out vec2 v_TexCoord;
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
    gl_Position = u_Projection * u_View * u_Model * vec4(position, 1.0);

    v_TexCoord = texCoord;

    mat3 normalMatrix = transpose(inverse(mat3(u_Model)));
    vec3 T = normalize(normalMatrix * tangent);
    vec3 B = normalize(normalMatrix * bitangent);
    vec3 N = normalize(normalMatrix * normal);
    //T = normalize(T - dot(T, N) * N);
    //vec3 B = cross(N, T);

    vec3 v_FragPos = vec3(u_Model * vec4(position, 1.0));

    mat3 TBN = transpose(mat3(T, B, N));
    tangentLightPos = TBN * u_lightPos0;
    tangentViewPos = TBN * u_CameraPos;
    tangentFragPos = TBN * v_FragPos;

   
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

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

vec3 m_diffuse = texture(u_diffuseMap, v_TexCoord).rgb;
float m_specular = texture(u_specularMap, v_TexCoord).r;
vec3 m_normal = texture(u_normalMap, v_TexCoord).rgb;
float AO = texture(u_AO, v_TexCoord).r;
float specularStrength = texture(u_roughness, v_TexCoord).r;


//ligths still have to be put in here manually
#define LIGHT_COUNT = 2;

void main()
{
    //normal map to values from -1 to 1
    vec3 normal = m_normal;
    normal = normalize(normal * 2.0 - 1.0);  // this normal is in tangent space

    //ambient
    vec3 ambient = m_diffuse * u_AmbientStrength * AO;
    //diffuse
    vec3 lightDir = normalize(tangentLightPos - tangentFragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * m_diffuse * u_lightColor;
    //specular
    vec3 viewDir = normalize(tangentViewPos - tangentFragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float random_metallness = mix(64, 32, (1.0 - m_specular)); 
    float spec = pow(max(dot(normal, halfwayDir), 0.0), random_metallness);
    //float spec = pow(max(dot(normal, halfwayDir), 0.0), u_Shininess);
    vec3 specular = (1.0 - specularStrength) * spec * u_lightColor;
    
    //result
    color = vec4(ambient + diffuse + specular, 1.0);
}