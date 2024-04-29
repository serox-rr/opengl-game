#version 460 core
#define M_PI 3.1415926535897932384626433832795
layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0
uniform mat4 transpose;
uniform mat4 model;
uniform float time;

void main()
{
    gl_Position = transpose * model * vec4(aPos, 1.0f);
}
//
