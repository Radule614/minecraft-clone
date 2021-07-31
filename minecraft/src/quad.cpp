#include "quad.h"

glm::vec2 Quad::textureCoordinates[4] = {
	glm::vec2(0.0f, 0.0f),
	glm::vec2(0.0f, 1.0f),
	glm::vec2(1.0f, 1.0f),
	glm::vec2(1.0f, 0.0f)
};

glm::vec3 Quad::getNormal(Face f)
{
	switch (f)
	{
	case FRONT:		return	glm::vec3(0.0f, 0.0f, 1.0f);
	case BACK:		return	glm::vec3(0.0f, 0.0f, -1.0f);
	case LEFT:		return	glm::vec3(-1.0f, 0.0f, 0.0f);
	case RIGHT:		return	glm::vec3(1.0f, 0.0f, 0.0f);
	case TOP:		return	glm::vec3(0.0f, 1.0f, 0.0f);
	case BOTTOM:	return	glm::vec3(0.0f, -1.0f, 0.0f);
	default:
		break;
	}
}

void Quad::getPositions(Face f, glm::vec3 arr[4])
{
	glm::vec3 positions[4];
	switch (f)
	{
	case FRONT:
		positions[0] = glm::vec3(-1.0f, -1.0f, 1.0f);
		positions[1] = glm::vec3(-1.0f, 1.0f, 1.0f);
		positions[2] = glm::vec3(1.0f, 1.0f, 1.0f);
		positions[3] = glm::vec3(1.0f, -1.0f, 1.0f);
		break;
	case BACK:
		positions[0] = glm::vec3(-1.0f, -1.0f, -1.0f);
		positions[1] = glm::vec3(-1.0f, 1.0f, -1.0f);
		positions[2] = glm::vec3(1.0f, 1.0f, -1.0f);
		positions[3] = glm::vec3(1.0f, -1.0f, -1.0f);
		break;
	case LEFT:
		positions[0] = glm::vec3(-1.0f, -1.0f, -1.0f);
		positions[1] = glm::vec3(-1.0f, 1.0f, -1.0f);
		positions[2] = glm::vec3(-1.0f, 1.0f, 1.0f);
		positions[3] = glm::vec3(-1.0f, -1.0f, 1.0f);
		break;
	case RIGHT:
		positions[0] = glm::vec3(1.0f, -1.0f, 1.0f);
		positions[1] = glm::vec3(1.0f, 1.0f, 1.0f);
		positions[2] = glm::vec3(1.0f, 1.0f, -1.0f);
		positions[3] = glm::vec3(1.0f, -1.0f, -1.0f);
		break;
	case TOP:
		positions[0] = glm::vec3(-1.0f, 1.0f, 1.0f);
		positions[1] = glm::vec3(-1.0f, 1.0f, -1.0f);
		positions[2] = glm::vec3(1.0f, 1.0f, -1.0f);
		positions[3] = glm::vec3(1.0f, 1.0f, 1.0f);
		break;
	case BOTTOM:
		positions[0] = glm::vec3(-1.0f, -1.0f, 1.0f);
		positions[1] = glm::vec3(-1.0f, -1.0f, -1.0f);
		positions[2] = glm::vec3(1.0f, -1.0f, -1.0f);
		positions[3] = glm::vec3(1.0f, -1.0f, 1.0f);
		break;
	}
	memcpy(arr, positions, sizeof(positions));
}