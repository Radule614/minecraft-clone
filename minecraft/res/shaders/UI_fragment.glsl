#version 330 core

out vec4 outColor;

in vec2 texCoords;

uniform sampler2D crosshair;

void main()
{
	outColor = texture(crosshair, texCoords);
}