#version 330 core

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

in VS_OUT {
    vec2 TexCoords;
	//vec3 Normal;
	//vec3 FragPos;

	//vec4 FragPosLightSpace; //shad
} inArgs; 

void main()
{       
	//we render to depth map so no coulor output needed
    gl_FragDepth =  gl_FragCoord.z;

	float alpha = texture(material.diffuse[0], inArgs.TexCoords).w;
	if(alpha < 1)
	{
		gl_FragDepth = 1; //if see through, put it furhtest back, to be discarded
		//return 0; //no shadow for see through parts
	}
} 