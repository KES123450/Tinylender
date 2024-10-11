#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aTexCoord;
layout (location = 3) in vec3 aColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 cameraPosition;
uniform vec3 val=vec3(0.5f);
uniform vec3 inColor;
out vec3 objectColor;
out vec3 normal;
out vec3 FragPos;
out vec3 cameraPos;

void main()
{
   normal= mat3(transpose(inverse(model)))* aNormal;
   objectColor=inColor;
   FragPos=vec3(model * vec4(aPos, 1.0));
   cameraPos=cameraPosition;
   gl_Position = model*vec4(aPos,1.0f);
}