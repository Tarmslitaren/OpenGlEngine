#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 projection;
uniform mat4 view;

void main()
{
   // TexCoords = aPos;
    //gl_Position = projection * view * vec4(-aPos, 1.0);
	//gl_Position = projection * view * vec4(aPos, 1.0);
	//aPos is flipped because we didn't set stbi_set_flip_vertically_on_load(false);
	//however if we do set that then we have other problems with reflect shaders.

	TexCoords = aPos;
    vec4 pos = projection * view * vec4(-aPos, 1.0);
    gl_Position = pos.xyww; //this to set z to 1: max depth value
}  