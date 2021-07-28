#version 330 core
out vec4 outColor;

in vec3 normal;
in vec2 texCoord;
in vec3 fragPos;

void main(){
	outColor = vec4(0.4, 0.4, 0.4, 1.0);
}