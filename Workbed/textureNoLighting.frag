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


void main()
{
    FragColor = texture(material.diffuse[0], inArgs.TexCoords);
}