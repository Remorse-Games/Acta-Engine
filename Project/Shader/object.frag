#version 330 core
out vec4 FragColor;

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

in vec3 Normal;  
in vec3 FragPos;  
in vec3 LightPos; 

uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 viewPos;

uniform Material material;

void main()
{
    // ambient
    vec3 ambient = material.ambient * lightColor;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(LightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = (diff * material.diffuse) * lightColor;

    // specular
    vec3 viewDir = normalize(-FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = (material.specular * spec) * lightColor;
            
    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
} 