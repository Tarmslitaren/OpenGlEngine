#version 330 core
out vec4 FragColor;
  
in vec2 TexCoords;

uniform sampler2D screenTexture;

void main()
{ 
	
    FragColor = texture(screenTexture, TexCoords);
	//grayscale
    float average = 0.2126 * FragColor.r + 0.7152 * FragColor.g + 0.0722 * FragColor.b;
    vec4 fragColor = vec4(average, average, average, 1.0);

		// apply gamma correction
    float gamma = 2.2;
    FragColor.rgb = pow(fragColor.rgb, vec3(1.0/gamma));
	FragColor.a = 1;
}