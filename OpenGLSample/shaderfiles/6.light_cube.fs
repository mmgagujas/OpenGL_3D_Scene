#version 330 core
uniform vec4 lightColor;

out vec4 FragColor;

void main()
{
    FragColor = lightColor; // set alle 4 vector values to 1.0
}