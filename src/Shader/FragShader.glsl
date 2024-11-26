#version 330 core

out vec4 FragColor;
in vec3 normal;
in vec3 objectColor;
in vec3 FragPos;
in vec3 cameraPos;

void main()
{
    vec3 norm = normalize(normal);
    vec3 viewDir = normalize(cameraPos - FragPos);
    vec3 result;
    vec3 lightPos= vec3(0.3f,0.7f,1.0f);

    //ambient light
    vec3 ambient = vec3(0.3f,0.3f,0.3f);

    // diffuse light
    vec3 lightDir = normalize(lightPos-FragPos);
    float diff = max(dot(normal,lightDir),0.0);
    vec3 diffuse = diff*vec3(0.3f,0.3f,0.3f);

    //specular light
    vec3 reflectDir = reflect(-lightDir,normal);
    float spec = pow(max(dot(viewDir,reflectDir),0.0),32);
    vec3 specular = spec*vec3(0.3f,0.3f,0.3f);

    result = (ambient+diffuse+specular)*objectColor;
    FragColor = vec4(result, 1.0);
}