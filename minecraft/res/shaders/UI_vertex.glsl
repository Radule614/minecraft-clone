#version 330 core

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec2 inTexCoords;

out vec2 texCoords;

uniform mat4 projection;

void main()
{
	gl_Position = projection * vec4(inPos, 1.0);
	texCoords = vec2(inTexCoords.x, 1 - inTexCoords.y);
}