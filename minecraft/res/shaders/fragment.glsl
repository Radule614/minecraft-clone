#version 330 core
out vec4 outColor;

in vec3 normal;
in vec2 texCoord;
in vec3 fragCoord;
in flat float texNum;

uniform sampler2D tex0;
uniform sampler2D tex1;
uniform sampler2D tex2;

void main(){
	vec4 texColor;

	if(texNum == 0) texColor = texture(tex0, texCoord);
	if(texNum == 1) texColor = texture(tex1, texCoord);
	if(texNum == 2) texColor = texture(tex2, texCoord);

	vec3 lightColor = vec3(1);
	vec3 lightDir = normalize(vec3(1, 1, 1));
	
	
	float ambientStrength = 0.4;
	vec3 ambient = ambientStrength * lightColor;


	float diff = max(dot(lightDir, normal), 0.0);
	vec3 diffuse = diff * lightColor;

	vec3 result = (ambient + diffuse) * vec3(texColor);
	outColor = vec4(result, 1.0);

}