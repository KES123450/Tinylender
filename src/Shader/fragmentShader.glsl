#version 330 core

uniform vec3 val;
out vec4 FragColor;
in vec3 color;
void main()
{
   FragColor = vec4(color.x, color.y, color.z*2.5f, 1.0f);

}