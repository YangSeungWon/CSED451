#version 330 core
out vec4 FragColor;

uniform vec4 uniformColor;

void main()
{
    FragColor = uniformColor;
}   