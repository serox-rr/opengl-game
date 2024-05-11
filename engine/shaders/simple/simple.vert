#version 460 core
layout (location = 0) in vec3 aPos;
uniform mat4 transpose;
uniform mat4 model;

void main()
{
    gl_PointSize = 15.0;
    gl_Position = transpose * model * vec4(aPos, 1.0f);
}
//
