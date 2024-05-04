#version 460 core
#define M_PI 3.1415926535897932384626433832795
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
uniform mat4 transpose;
uniform mat4 model;
uniform mat3 modelNormal;
out vec3 FragPos;
out vec3 Normal;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = modelNormal * aNormal;
    gl_Position = transpose * vec4(aPos, 1.0f);
}
//
