#version 460 core

in vec3 FragPos;
in float Height;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform mat4 model;

out vec4 FragColor;

void main()
{
    vec3 x = dFdx(FragPos); // "FragPos = vec3(model * p);" from the tess eval
    vec3 y = dFdy(FragPos);
    vec3 normal = inverse(mat3(model)) * normalize(cross(x, y));
    // ambient
    float ambientStrength = 0.5;
    vec3 ambient = ambientStrength * lightColor;

    // diffuse
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 3);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 result = (ambient + diffuse) * objectColor;
    FragColor = vec4(result, 1.0);
}
