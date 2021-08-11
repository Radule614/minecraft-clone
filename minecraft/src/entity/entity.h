#pragma once

#include "glm/glm.hpp"

class Entity {
public:
	Entity(glm::vec3 pos) : position(pos)
	{

	}

	void move();
private:
	glm::vec3 position;
};