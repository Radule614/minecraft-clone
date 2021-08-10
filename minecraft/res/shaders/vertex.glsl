#version 330 core

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;
layout(location = 3) in vec2 inTexId;
layout(location = 4) in vec3 inOffset;

out vec3 normal;
out vec2 texCoord;
out vec3 fragCoord;

uniform float texture_size;
uniform float atlas_size;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	vec3 offsetPos = inPos + inOffset;
	gl_Position = projection * view * model * vec4(offsetPos, 1.0f);
	normal = mat3(transpose(inverse(model))) * inNormal;
	fragCoord = vec3(model * (offsetPos, 1.0f));

	if(inTexCoord.x == 0.0 && inTexCoord.y == 0.0)
	{
		texCoord = vec2(inTexId.x * texture_size /atlas_size, 1 - ((atlas_size-(inTexId.y+1) * texture_size)/atlas_size));
	} 
	else if(inTexCoord.x == 0.0 && inTexCoord.y == 1.0)
	{
		texCoord = vec2(inTexId.x * texture_size /atlas_size, 1 - ((atlas_size-inTexId.y * texture_size)/atlas_size));
	}
	else if(inTexCoord.x == 1.0 && inTexCoord.y == 1.0)
	{
		texCoord = vec2((inTexId.x+1) * texture_size /atlas_size, 1 - ((atlas_size-inTexId.y * texture_size)/atlas_size));
	}
	else
	{
		texCoord = vec2((inTexId.x+1) * texture_size /atlas_size, 1 - ((atlas_size-(inTexId.y+1) * texture_size)/atlas_size));
	}
}