#version 330 core
layout (location = VERTEX_LAYOUT_POSITION) in vec3 aPos;

out vec3 ourColor;
out vec2 TexCoord;
uniform mat4 transform;
uniform mat4 model;
layout (std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
};
void main()
{
    //gl_Position = transform *  vec4(aPos, 1.0);
	gl_Position = projection * view * model * vec4(aPos, 1.0);
    //ourColor = aColor;
    //TexCoord = vec2(aTexCoord.x, aTexCoord.y);;
}