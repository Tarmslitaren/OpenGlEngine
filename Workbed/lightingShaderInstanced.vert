#version 330 core
layout (location = VERTEX_LAYOUT_POSITION) in vec3 aPos;
layout (location = VERTEX_LAYOUT_NORMALS) in vec3 aNormal;
layout (location = VERTEX_LAYOUT_TEXCOORDS) in vec2 aTexCoords;
layout (location = VERTEX_LAYOUT_INSTANCE_MATRIX) in mat4 aInstanceMatrix;



out VS_OUT {
    vec2 TexCoords;
	vec3 Normal;
	vec3 FragPos;
} vs_out; 
//uniform mat4 model;
layout (std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
};
void main()
{
	
	
	vs_out.TexCoords = aTexCoords;
	//TexCoords = aTexCoords;
	vs_out.FragPos = vec3(aInstanceMatrix * vec4(aPos, 1.0));
	//vs_out.Normal = aNormal;
	vs_out.Normal = mat3(transpose(inverse(aInstanceMatrix))) * aNormal;  //this is the normal matrix: needed if any scaling is done.

	gl_Position = projection * view * vec4(vs_out.FragPos, 1.0);
}