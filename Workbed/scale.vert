#version 330 core
layout (location = VERTEX_LAYOUT_POSITION) in vec3 aPos;
layout (location = VERTEX_LAYOUT_NORMALS) in vec3 aNormal;
layout (location = VERTEX_LAYOUT_TEXCOORDS) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 model;
layout (std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
};

out vec3 Normal;
out vec3 FragPos; 

uniform float scaleUp;

void main()
{
	FragPos = vec3(model * vec4(aPos, 1.0));
	Normal = mat3(transpose(inverse(model))) * aNormal;
    TexCoords = aTexCoords;    
	gl_Position = projection * view * model * vec4(aPos + aNormal*scaleUp, 1.0);
}