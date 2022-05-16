#version 330 core
in vec4 color;
out vec4 FragColor;

uniform vec4 uniformColor;

void main()
{
    FragColor = color;
}   