#version 330 core
out vec4 outColor;

in vec3 normal;
in vec2 texCoord;
in vec3 fragCoord;

uniform sampler2D atlas;

void main(){
	vec4 texColor;
	texColor = texture(atlas, texCoord);

	vec3 lightColor = vec3(1);
	vec3 lightDir = normalize(vec3(1, 2, 1));
	
	
	float ambientStrength = 0.5;
	vec3 ambient = ambientStrength * lightColor;


	float diff = max(dot(lightDir, normal), 0.0);
	vec3 diffuse = diff * lightColor;

	vec3 result = (ambient + diffuse) * vec3(texColor);
	outColor = vec4(result, texColor.w);
}