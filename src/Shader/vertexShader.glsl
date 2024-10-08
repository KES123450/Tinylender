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
   //vec3 lightDir =vec3(0.5f,0.1f,0.2f);
   //vec4 normal = projection*view*model*vec4(aNormal.x,aNormal.y,aNormal.z,1.0f); 
   normal= aNormal;
   objectColor=inColor;
   FragPos=vec3(model * vec4(aPos, 1.0));
   cameraPos=cameraPosition;
   //dirLightsData=dirLights;
   //lightColorData=dirLights[0].lightColor;
   //gl_Position = projection*view*model* vec4(aPos.x, aPos.y, aPos.z, 1.0);
   gl_Position = model*vec4(aPos,1.0f);
}