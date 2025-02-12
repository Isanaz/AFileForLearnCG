#version 330 core
layout (location = 0) in vec3 aPos;

uniform float add;

out vec3 ourColor;

void main()
{
    gl_Position = vec4(aPos.x + add, aPos.y, aPos.z, 1.0);
    ourColor = aPos;
}