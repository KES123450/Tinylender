#version 330 core

out vec4 FragColor;
in vec2 texCoord;

uniform sampler2D outTexture;
uniform vec4 pushedColor;
void main()
{
   FragColor = texture(outTexture,texCoord)*pushedColor;

}