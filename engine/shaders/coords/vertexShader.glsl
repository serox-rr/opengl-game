#version 330 core
#define M_PI 3.1415926535897932384626433832795
layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0
layout (location = 1) in vec3 indices;
uniform mat4 transpose;
uniform float time;
void main()
{
    gl_Position = transpose * vec4(aPos.x, (sin(aPos.x*M_PI/100)*100+sin(aPos.x*M_PI/10)*10+sin(aPos.z*M_PI/10-time)*10)/120*100, aPos.z, 1.0f);
}
//
