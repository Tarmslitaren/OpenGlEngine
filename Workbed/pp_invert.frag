#version 330 core
out vec4 FragColor;
  
in vec2 TexCoords;

uniform sampler2D screenTexture;

void main()
{ 
	//invert
	vec4 fragColor = vec4(vec3(1.0 - texture(screenTexture, TexCoords)), 1.0);

			// apply gamma correction
    float gamma = 2.2;
    FragColor.rgb = pow(fragColor.rgb, vec3(1.0/gamma));
	FragColor.a = 1;
}