#version 330 core

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;
layout(location = 3) in float inTexNum;
layout(location = 4) in vec3 inOffset;

out vec3 normal;
out vec2 texCoord;
out float texNum;
out vec3 fragCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	vec3 offsetPos = inPos + inOffset;
	gl_Position = projection * view * model * vec4(offsetPos, 1.0f);
	normal = mat3(transpose(inverse(model))) * inNormal;
	fragCoord = vec3(model * (offsetPos, 1.0f));
	texCoord = vec2(inTexCoord.x, 1 - inTexCoord.y);
	texNum = inTexNum;
}