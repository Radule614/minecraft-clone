#pragma once

#include "../world/world.hpp"
#include "../ray.hpp"

#include "glm/glm.hpp"

class Entity {
public:
	Entity(glm::vec3 pos, glm::vec3 size) : position(pos), size(size)
	{

	}

	void move();
	glm::vec3 position;
	glm::vec3 size;
public:
};