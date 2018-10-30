#version 330 core
out vec4 FragColor;
  

//uniform vec3 viewPos; //camera
in VS_OUT {
    vec2 TexCoords;
	vec3 Normal;
	vec3 FragPos;
} inArgs; 

#define MAX_NR_TEXTURE 4  
struct Material {
    vec3 ambient;//not used: amibient will equal diffuse map in most cases
	int nrOfDiffuse;
	int nrOfSpecular;
    sampler2D diffuse[MAX_NR_TEXTURE];
    sampler2D specular[MAX_NR_TEXTURE];
    float shininess;
}; 
uniform Material material;


struct DirectionalLight {
    vec3 direction;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  
uniform DirectionalLight dirLight;

struct PointLight {    
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;  

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  
//fuu this
#define MAX_NR_POINT_LIGHTS 10 
uniform PointLight pointLights[MAX_NR_POINT_LIGHTS];
uniform int nrPointLights;

struct SpotLight {    
    vec3 position;
	vec3 direction;
    
    float constant;
    float linear;
    float quadratic;  

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

	float cutOff;
	float outerCutOff;
};   
uniform SpotLight spotLight;



//forward declare functions:
vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir);
vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);  
vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir); 

//this is phong lighting model: ambient + diffuse + specular
void main()
{

    // properties
    vec3 norm = normalize(inArgs.Normal);

	//vec3 viewDir = normalize(-FragPos); // the viewer is always at (0,0,0) in view-space, so viewDir is (0,0,0) - Position => -Position
	vec3 viewDir = normalize(inArgs.FragPos); // fragpos should be inverted here, but there is something off about my view matrix
   // vec3 viewDir = normalize(viewPos - FragPos);//if calculating the angle in the vertex shader

    // phase 1: Directional lighting
    vec3 result = CalculateDirectionalLight(dirLight, norm, viewDir);
    // phase 2: Point lights
    for(int i = 0; i < nrPointLights; i++)
        result += CalculatePointLight(pointLights[i], norm, inArgs.FragPos, viewDir);    
    // phase 3: Spot light
    result += CalculateSpotLight(spotLight, norm, inArgs.FragPos, viewDir);    
    
	float alpha = texture(material.diffuse[0], inArgs.TexCoords).w; //should the alpha be affected by lighting model?
    FragColor = vec4(result, alpha);
}

vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading: the closer to surface normal the brighter
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse[0], inArgs.TexCoords));
	//vec3 ambient = light.ambient * material.ambient; //if not using texture
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse[0], inArgs.TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular[0], inArgs.TexCoords)); //specular: effect higher the smaller reverse angle from view.
	//vec3 specular = light.specular * (spec * material.specular);  //if not using specular map
    return (ambient + diffuse + specular);
}  

vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading: he closer to surface normal the brighter
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance +  light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse[0], inArgs.TexCoords));
	//vec3 ambient = light.ambient * material.ambient; //if not using texture
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse[0], inArgs.TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular[0], inArgs.TexCoords)); //specular: effect higher the smaller reverse angle from view.
	//vec3 specular = light.specular * (spec * material.specular);  //if not using specular map

    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
} 

vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading: he closer to surface normal the brighter
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance +  light.quadratic * (distance * distance));    
    

		//spotlight
	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon   = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);  


	// combine results
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse[0], inArgs.TexCoords));
	//vec3 ambient = light.ambient * material.ambient; //if not using texture
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse[0], inArgs.TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular[0], inArgs.TexCoords)); //specular: effect higher the smaller reverse angle from view.
	//vec3 specular = light.specular * (spec * material.specular);  //if not using specular map

    ambient  *= attenuation * intensity;
    diffuse  *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}