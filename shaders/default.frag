#version 460 core
out vec4 FragColor;

in vec2 TexCoords;

uniform float ambientLightStrenght;
uniform vec3 lightColor;
uniform sampler2D texture_diffuse1;

void main()
{
    vec3 ambientLight = ambientLightStrenght * lightColor;

    vec3 result = ambientLight * texture(texture_diffuse1, TexCoords).rgb;
    FragColor = vec4(result, 1.0);
}