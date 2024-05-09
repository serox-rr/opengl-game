#version 460 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;
in float Height;

uniform vec3 viewPos;
uniform mat4 model;
uniform Material material;
uniform Light light;

out vec4 FragColor;


void main()
{
    vec3 x = dFdx(FragPos); // "FragPos = vec3(model * p);" from the tess eval
    vec3 y = dFdy(FragPos);
    vec3 normal = inverse(mat3(model)) * normalize(cross(x, y));



    vec3 ambient = light.ambient * material.ambient;

    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff * material.diffuse);

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}
