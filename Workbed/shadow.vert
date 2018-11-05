#version 330 core
layout (location = VERTEX_LAYOUT_POSITION) in vec3 aPos;

uniform mat4 lightSpaceMatrix;
uniform mat4 model;

void main()
{
	//render from dir light point of view
    gl_Position = lightSpaceMatrix * model * vec4(aPos, 1.0);
}  