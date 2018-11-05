#version 330 core
layout (location = VERTEX_LAYOUT_POSITION) in vec3 aPos;
layout (location = VERTEX_LAYOUT_TEXCOORDS) in vec2 aTexCoords;

out vec2 TexCoords;
uniform mat4 lightSpaceMatrix;
uniform mat4 model;
layout (std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
};
void main()
{
	TexCoords = aTexCoords;
	//gl_Position = lightSpaceMatrix * model * vec4(aPos, 1.0);
	//gl_Position = lproj * lview * model * vec4(aPos, 1.0);

	//gl_Position = projection * view * model * vec4(aPos, 1.0);
	gl_Position = model * vec4(aPos, 1.0); //screensapace
}
