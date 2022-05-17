#version 330 core
in vec4 color;
out vec4 FragColor;
in vec2 texCoord;
uniform bool isTexture;
uniform sampler2D texture;

void main()
{
    FragColor = color;
    if (isTexture) {
        FragColor = color * texture2D(texture, texCoord);
    }
}