#version 330 core
layout (location = VERTEX_LAYOUT_POSITION) in vec3 aPos;

layout (location = VERTEX_LAYOUT_TEXCOORDS) in vec2 aTexCoords; //for see through objects

uniform mat4 lightSpaceMatrix;
uniform mat4 model;

out VS_OUT {
    vec2 TexCoords;
	//vec3 Normal;
	//vec3 FragPos;

	//vec4 FragPosLightSpace;
} vs_out; 

void main()
{
	vs_out.TexCoords = aTexCoords;
	//render from dir light point of view
    gl_Position = lightSpaceMatrix * model * vec4(aPos, 1.0);
}  