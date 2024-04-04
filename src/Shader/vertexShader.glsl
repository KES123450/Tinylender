#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out vec3 color;

void main()
{
   //vec3 lightDir =vec3(0.5f,0.1f,0.2f);
   //vec4 normal = projection*view*model*vec4(aNormal.x,aNormal.y,aNormal.z,1.0f); 
   color=aColor;
   gl_Position = projection*view*model* vec4(aPos.x, aPos.y, aPos.z, 1.0);
}