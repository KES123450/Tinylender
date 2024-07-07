#version 330 core

out vec4 FragColor;
in vec2 texCoord;

uniform sampler2D outTexture;
uniform vec4 pushedColor;
void main()
{
    vec4 maskColor=vec4(0.2f,0.1f,0.8f,0.3f);
   // if(maskColor.a <=0.0f)
      //  discard;
   FragColor = maskColor;

}