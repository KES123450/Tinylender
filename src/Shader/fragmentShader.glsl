#version 330 core

out vec4 FragColor;
in vec3 color;
in vec3 valColor;
in vec3 FragPos;
in vec3 cameraPos;

void main()
{

    // diffuse 
    vec3 norm = normalize(color);
    vec3 lightDir = normalize(vec3(0.3f,0.2f,0.7f) - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff*vec3(1.0f,1.0f,1.0f);

    // specular
    //float specularStrength = 0.5;
    //vec3 viewDir = normalize(cameraPos - FragPos);
    //vec3 reflectDir = reflect(-lightDir, norm);  
    //float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    //vec3 specular = specularStrength * spec * vec3(1.0f,1.0f,1.0f);  
        
    vec3 result = (diffuse) * valColor;
    //FragColor = vec4(result.x+0.2f,result.y+0.2f,result.z+0.2f, 1.0);

   FragColor = vec4(((color.x+1)/2)*valColor.x+0.2f, ((color.y+1)/2)*valColor.y+0.2f, ((color.z+1)/2)*valColor.z+0.2f, 1.0f);
   //FragColor = vec4(valColor.x,valColor.y,valColor.z, 1.0f);
}