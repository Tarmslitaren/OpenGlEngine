#version 330 core
out vec4 FragColor;
  
in vec3 Normal;  
in vec3 FragPos; 

//uniform vec3 lightPos;  
//in vec3 LightPos;
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
    vec3 position; // No longer necessery when using directional lights.
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

	float constant;
	float linear;
	float quadratic;
	 //for spotlight
	float cutOff;

};

uniform Light light;  

//this is phong lighting model: ambient + diffuse + specular
void main()
{


	//ambient
	vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));
	//vec3 ambient = light.ambient * material.ambient; //if not using texture
  

     // diffuse calcuations
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
	//vec3 lightDir = normalize(-light.direction); //for directional light

	//spotlight
	float theta = dot(lightDir, normalize(-light.direction));
	if(theta > light.cutOff) 
	{  

		float diff = max(dot(norm, lightDir), 0.0);
		//calc diffuse strength: the closer to surface normal the brighter
		vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords)); 

		//specular: effect higher the smaller reverse angle from view.
		//vec3 viewDir = normalize(viewPos - FragPos); //if calculating the angle in the vertex shader
		//vec3 viewDir = normalize(-FragPos); // the viewer is always at (0,0,0) in view-space, so viewDir is (0,0,0) - Position => -Position
		vec3 viewDir = normalize(FragPos); // fragpos should be inverted here, but there is something off about my view matrix
		vec3 reflectDir = reflect(-lightDir, norm); 
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
		vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
		//vec3 specular = light.specular * (spec * material.specular);  //if not using specular map

		//calc attenuation (not for directional lights)
		float distance    = length(light.position - FragPos);
		float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));  
		//ambient *= attenuation;
		diffuse *= attenuation;
		specular *= attenuation;

     
		FragColor = vec4(ambient + diffuse + specular, 1.0);  
	}
	else
	{
		FragColor = vec4(ambient, 1.0);  
	}
}