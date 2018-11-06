#version 330 core
out vec4 FragColor;
  

//uniform vec3 viewPos; //camera
in VS_OUT {
    vec2 TexCoords;
	vec3 Normal;
	vec3 FragPos;

	vec4 FragPosLightSpace; //shad
} inArgs; 

uniform sampler2D shadowMap;//shad

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
	vec3 position; //for shadows
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

float ShadowCalculation(vec4 fragPosLightSpace , vec3 lightDir)
{
	// perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w; //this step is meaningless if using ortho projection

	if(projCoords.z > 1.0) //if outside the frustums length then no shadows
	{
        return 0;
	}

	//Because the depth from the depth map is in the range [0,1] and we also want to use projCoords to sample from the depth map so we transform the NDC coordinates to the range [0,1]:
	projCoords = projCoords * 0.5 + 0.5; 
	//closest depth from the light's point of view:
	float closestDepth = texture(shadowMap, projCoords.xy).r;  
	// get depth of current fragment from light's perspective
	float currentDepth = projCoords.z;  
	 // check whether current frag pos is in shadow
	 //float bias = 0.00005; //to solve shadow acne. bias values need to be tweaked per scene :(
	 vec3 norm = normalize(inArgs.Normal);
	 float bias = max(0.003 * (1.0 - dot(norm, lightDir)), 0.00005); 

	//float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0; 


	//percentage close filtering (PCF) smapling surrounding texels in the shadowmap to smooth the edges
	//By using more samples and/or varying the texelSize variable you can increase the quality of the soft shadows.
	float shadow = 0.0;
	vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
	int sampleSize = 1;
	for(int x = -sampleSize; x <= sampleSize; ++x)
	{
		for(int y = -sampleSize; y <= sampleSize; ++y)
		{
			float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
			shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;        
		}    
	}
	int nrSamples =(1 + (sampleSize*2)) * (1 + (sampleSize*2));
	shadow /= nrSamples;


	//shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0; //override smoothness
	return shadow;
}

//this is blinn-phong lighting model: ambient + diffuse + specular
void main()
{

    // properties
    vec3 norm = normalize(inArgs.Normal);

	//vec3 viewDir = normalize(-FragPos); // the viewer is always at (0,0,0) in view-space, so viewDir is (0,0,0) - Position => -Position
	vec3 viewDir = normalize(inArgs.FragPos); // fragpos should be inverted here, but there is something off about my view matrix
   // vec3 viewDir = normalize(viewPos - FragPos);//if calculating the angle in the vertex shader

   //todo: variable amount of dirlights and spotlights
    // phase 1: Directional lighting
    vec3 result = CalculateDirectionalLight(dirLight, norm, viewDir);
    // phase 2: Point lights
    //for(int i = 0; i < nrPointLights; i++)
    //    result += CalculatePointLight(pointLights[i], norm, inArgs.FragPos, viewDir);    
    // phase 3: Spot light
    //result += CalculateSpotLight(spotLight, norm, inArgs.FragPos, viewDir);


	float alpha = texture(material.diffuse[0], inArgs.TexCoords).w; //should the alpha be affected by lighting model?
    vec4 fragColor = vec4(result, alpha);

    //vec4 fragColor = vec4(result, 1.0);

	// apply gamma correction todo: remove this when we have post process working again
    float gamma = 2.2;
    FragColor.rgb = pow(fragColor.rgb, vec3(1.0/gamma));
    //FragColor = fragColor;
}

vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - inArgs.FragPos); //this?  normalize(-light.direction);
    // diffuse shading: the closer to surface normal the brighter
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal); //phong
	vec3 halfwayDir = normalize(lightDir + viewDir);  //this is blinn phong (generally the shininess varable needs to be 2-4 times as much for a similar result as normal phong
    float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
    // combine results
	vec3 color = texture(material.diffuse[0], inArgs.TexCoords).rgb;
    vec3 ambient  = light.ambient * color;
	//vec3 ambient = light.ambient * material.ambient; //if not using texture
    vec3 diffuse  = light.diffuse  * diff;
    vec3 specular = light.specular * spec; //specular: effect higher the smaller reverse angle from view.
	//vec3 specular = light.specular * (spec * material.specular);  //if not using specular map
	vec3 specMapColor = vec3(texture(material.specular[0], inArgs.TexCoords));
   	    // calculate shadow
    float shadow = ShadowCalculation(inArgs.FragPosLightSpace, lightDir);       
    //vec3 lighting = ambient + (1.0 - shadow) * (diffuse + specular);      //multiply the diffuse and specular contributions by the inverse of the shadow component e.g. how much the fragment is not in shadow
	 vec3 lighting = (  ambient * color  + (1.0 - shadow) * (diffuse * color + specular * specMapColor)  );

   
   return lighting;// (ambient + diffuse + specular);
}


vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading: he closer to surface normal the brighter
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    //vec3 reflectDir = reflect(-lightDir, normal); //phong
	//float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 halfwayDir = normalize(lightDir + viewDir);  //this is blinn phong (generally the shininess varable needs to be 2-4 times as much for a similar result as normal phong
    float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
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
    //vec3 reflectDir = reflect(-lightDir, normal); //phong
	//float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 halfwayDir = normalize(lightDir + viewDir);  //this is blinn phong (generally the shininess varable needs to be 2-4 times as much for a similar result as normal phong
    float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
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

	   	    // calculate shadow
    float shadow = ShadowCalculation(inArgs.FragPosLightSpace, lightDir);       
    vec3 lighting = ambient + (1.0 - shadow) * (diffuse + specular);  

    return lighting;// (ambient + diffuse + specular);
}