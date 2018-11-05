#version 330 core
out vec4 FragColor;
in vec2 TexCoords;

//float near = 0.1; 
//float far  = 100.0; 

uniform float nearPlane;
uniform float farPlane;
uniform sampler2D depthMap;
  
// required when using a perspective projection matrix
float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0; // Back to NDC 
    return (2.0 * nearPlane * farPlane) / (farPlane + nearPlane - z * (farPlane - nearPlane));	
}

void main()
{
	//for debugging actual depthbuffer
    //float depth = LinearizeDepth(gl_FragCoord.z) / farPlane; // divide by far for demonstration
    //FragColor = vec4(vec3(depth), 1.0);
	//FragColor = vec4(vec3(gl_FragCoord.z), 1.0);

	//gl_FragDepth = gl_FragCoord.z;

	//debugging texture
	float depthValue = texture(depthMap, TexCoords).r;
    FragColor = vec4(vec3(LinearizeDepth(depthValue) / farPlane), 1.0); // perspective
    //FragColor = vec4(vec3(depthValue), 1.0); // orthographic
}