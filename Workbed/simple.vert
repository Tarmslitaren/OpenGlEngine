#version 330 core
layout (location = VERTEX_LAYOUT_POSITION) in vec3 aPos;
layout (location = VERTEX_LAYOUT_TEXCOORDS) in vec2 aTexCoords;
layout (location = VERTEX_LAYOUT_COLOR) in vec3 aColor;

out vec2 TexCoords;

out VS_OUT {
    vec3 color;
} vs_out;

uniform mat4 model;
layout (std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
};

void main()
{
	vs_out.color = aColor;
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
}