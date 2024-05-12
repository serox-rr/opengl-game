#version 460

in vec2 TextureCoords;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;


struct Light {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Material {
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
};

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main() {
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * light.diffuse;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = light.specular * (spec * vec3(texture(material.texture_specular1, TextureCoords)));
    vec3 result = (diffuse + specular) * vec3(texture(material.texture_diffuse1, TextureCoords));

    FragColor = texture(material.texture_diffuse1, TextureCoords);
}
