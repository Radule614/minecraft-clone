#version 330 core
out vec4 outColor;

in vec3 normal;
in vec2 texCoord;
in flat float texNum;

uniform sampler2D tex0;
uniform sampler2D tex1;
uniform sampler2D tex2;

void main(){
	if(texNum == 0) outColor = texture(tex0, texCoord);
	if(texNum == 1) outColor = texture(tex1, texCoord);
	if(texNum == 2) outColor = texture(tex2, texCoord);
}