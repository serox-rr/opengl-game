#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexture;

out vec2 TextureCoords;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 transpose;
void main()
{
    gl_Position = transpose * model * vec4(aPos, 1.0);
    TextureCoords = aTexture;
    Normal = mat3(transpose) * aNormal;
    FragPos = vec3(model * vec4(aPos, 1.0));
}
