#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;
out vec3 Normal;
out vec3 FragPos; 
//out vec3 LightPos;
//uniform vec3 lightPos; 
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main()
{
	TexCoords = aTexCoords;
	FragPos = vec3(model * vec4(aPos, 1.0));
	//Normal = aNormal;
	Normal = mat3(transpose(inverse(model))) * aNormal;  //this is the normal matrix: needed if any scaling is done. inverse is expensives os do on the cpu.
	//LightPos = vec3(view * vec4(lightPos, 1.0)); // Transform world-space light position to view-space light position

	gl_Position = projection * view * vec4(FragPos, 1.0);
}