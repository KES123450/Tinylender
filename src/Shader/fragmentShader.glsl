#version 330 core

out vec4 FragColor;
in vec3 color;
in vec3 valColor;
void main()
{
   //FragColor = vec4(((color.x+1)/2)*valColor.x, ((color.y+1)/2)*valColor.y, ((color.z+1)/2)*valColor.z, 1.0f);
   FragColor = vec4(0.5f,0.3f,0.7f, 1.0f);
}