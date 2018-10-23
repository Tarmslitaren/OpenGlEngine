#version 330 core
out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube skybox; //get's magically filled when binding a cubemap texture

void main()
{    
    FragColor = texture(skybox, TexCoords);
}