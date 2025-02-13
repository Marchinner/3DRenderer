#version 460 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

uniform vec3 directionalLightPosition;
uniform float ambientLightStrenght;
uniform vec3 lightColor;
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_normal1;
uniform vec3 viewPos;

float specularstrength = 0.5;

void main()
{
    //vec3 norm = normalize(Normal);
    vec3 norm = texture(texture_normal1, TexCoords).rgb;
    norm = normalize(norm * 2.0 - 1.0);
    vec3 lightDir = normalize(directionalLightPosition - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    vec3 ambientLight = ambientLightStrenght * lightColor;
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularstrength * spec * texture(texture_specular1, TexCoords).rgb;

    vec3 result = (ambientLight + diffuse + specular) * texture(texture_diffuse1, TexCoords).rgb;
    FragColor = vec4(result, 1.0);
}