#version 330 core

struct BlinnPhongLight
{
   vec3 lightColor;
   vec3 lightPos;
};

layout (std140) uniform Lights
{
    BlinnPhongLight lights[32];
};

out vec4 FragColor;
in vec3 normal;
in vec3 objectColor;
in vec3 FragPos;
in vec3 cameraPos;
 
vec3 CalcBlinnPhongLight(BlinnPhongLight light, vec3 normal, vec3 viewDir);

void main()
{
    FragColor = vec4(0.3f,0.3f,0.3f, 1.0f);
    
    vec3 norm = normalize(normal);
    vec3 viewDir = normalize(cameraPos - FragPos);
    vec3 result;
    for(int i=0; i<5; i++)
    {
        result+=CalcBlinnPhongLight(lights[i],norm,viewDir);
    }
    result *= objectColor;
    FragColor = vec4(result, 1.0);
}

vec3 CalcBlinnPhongLight(BlinnPhongLight light, vec3 normal, vec3 viewDir)
{
    //ambient light
    vec3 ambient = vec3(1.0,1.0,1.0)*light.lightColor;

    // diffuse light
    vec3 lightDir = normalize(light.lightPos-FragPos);
    float diff = max(dot(normal,lightDir),0.0);
    vec3 diffuse = diff*light.lightColor;

    //specular light
    vec3 reflectDir = reflect(-lightDir,normal);
    float spec = pow(max(dot(viewDir,reflectDir),0.0),32);
    vec3 specular = spec*light.lightColor;

    return (ambient+diffuse+specular);
}