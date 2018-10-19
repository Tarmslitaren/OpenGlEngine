#version 330 core
out vec4 FragColor;
  
in vec3 Normal;  
in vec3 FragPos; 

//uniform sampler2D texture1;
//uniform sampler2D texture2;

//uniform vec3 objectColor;
//uniform vec3 lightColor;

uniform vec3 lightPos;  
in vec3 LightPos;
//uniform vec3 viewPos; //camera

in vec2 TexCoords;
struct Material {
    vec3 ambient;//not used: amibient will equal diffuse map in most cases
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
}; 
uniform Material material;

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light light;  

//this is phong lighting model: ambient + diffuse + specular
void main()
{
    // ambient
    //vec3 ambient = light.ambient * material.ambient;
	//vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

     // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
	//vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));  
	//calc diffuse strength: the closer to surface normal the brighter

	//specular: effect higher the smaller reverse angle from view.
	//vec3 viewDir = normalize(viewPos - FragPos);
	//vec3 viewDir = normalize(-FragPos); // the viewer is always at (0,0,0) in view-space, so viewDir is (0,0,0) - Position => -Position
	vec3 viewDir = normalize(FragPos); // fragpos should be inverted here, but there is something off about my view matrix
	vec3 reflectDir = reflect(-lightDir, norm); 
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    //vec3 specular = light.specular * (spec * material.specular);  

	//vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
  
  
  vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));
vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));  
vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
FragColor = vec4(ambient + diffuse + specular, 1.0);  
	//FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
	//FragColor = vec4(lightColor * objectColor, 1.0);
}