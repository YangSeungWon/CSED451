#version 330 core
layout (location = 0) in vec3 aPos;
uniform mat4 model_view;
uniform mat4 projection;

void main()
{
    vec4 vPosition = vec4(aPos, 1.0);
    gl_Position = projection * model_view * vPosition/vPosition.w;
}      