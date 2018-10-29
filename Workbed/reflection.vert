#version 330 core
layout (location = VERTEX_LAYOUT_POSITION) in vec3 aPos;
layout (location = VERTEX_LAYOUT_NORMALS) in vec3 aNormal;
out vec3 Normal;
out vec3 Position;

uniform mat4 model;
layout (std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
};

void main()
{
    Normal = mat3(transpose(inverse(model))) * aNormal;
    Position = vec3(model * vec4(aPos, 1.0));
    gl_Position = projection * view * model * vec4(aPos, 1.0);
} 
