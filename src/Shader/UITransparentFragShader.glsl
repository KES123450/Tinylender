#version 330 core

out vec4 FragColor;
in vec2 texCoord;

uniform sampler2D outTexture;

void main()
{
  vec4 texColor = texture(outTexture, texCoord);
    if(texColor.a < 0.1)
        discard;
    FragColor = texColor;

}