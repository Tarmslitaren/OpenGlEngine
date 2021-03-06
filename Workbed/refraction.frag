#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 Position;

uniform vec3 cameraPos;
uniform samplerCube skybox;

void main()
{             

	//todo: ratio as uniform:
	//Material	Refractive index
	//Air		1.00
	//Water		1.33
	//Ice		1.309
	//Glass		1.52
	//Diamond	2.42



	float ratio = 1.00 / 1.52; //from air to glass
    vec3 I = normalize(Position - cameraPos);
    vec3 R = refract(I, normalize(Normal), -ratio); //flipped because, who knows why
    FragColor = vec4(texture(skybox, R).rgb, 1.0);
}