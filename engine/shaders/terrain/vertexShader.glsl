#version 330 core
layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0

out vec2 TexCoord;

uniform mat4 transpose;

void main()
{
    gl_Position =  transpose * instanceModel * vec4(aPos, 1.0);
}
