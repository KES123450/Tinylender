#version 330 core

uniform vec3 val;
out vec4 FragColor;
in vec3 color;
void main()
{
   FragColor = vec4(0.8f, 0.2f, 0.6f, 1.0f);

}