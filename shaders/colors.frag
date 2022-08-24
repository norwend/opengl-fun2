#version 330 core

out vec4 FragColor;
  
uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
    vec3 objColor = vec3(1.0f, 0.5f, 0.31f);
    float ambStrength = 0.1;
    vec3 ambient = ambStrength * lightColor;

    vec3 result = ambient * objColor;
    FragColor = vec4(result, 1.0);
}
