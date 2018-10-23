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
	//aPos is flipped because of differences between CU::Matrix and opengl format. voi ei. or faulty projection, maybe.

	TexCoords = aPos;
    vec4 pos = projection * view * vec4(-aPos, 1.0);
    gl_Position = pos.xyww; //this to set z to 1: max depth value
}  