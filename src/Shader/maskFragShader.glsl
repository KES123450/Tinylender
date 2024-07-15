#version 330 core

out vec4 FragColor;
in vec2 texCoord;

uniform sampler2D outTexture;
uniform vec4 pushedColor;
void main()
{
    vec4 maskColor=vec4(0.19607843137f,0.18823529411f,0.18431372549f,1.0f);
   // if(maskColor.a <=0.0f)
      //  discard;
   FragColor = maskColor;

}