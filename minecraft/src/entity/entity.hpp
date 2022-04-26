#pragma once

#include "../world/world.hpp"
#include "../ray.hpp"

#include "glm/glm.hpp"

class Entity {
public:
	Entity(World& w, glm::vec3 pos, glm::vec3 size, glm::vec3& vel, bool gravityON = false) 
		: world(w), position(pos), size(size), velocity(vel), gravityON(gravityON), moveComponent(glm::vec3(0)), gravityComponent(glm::vec3(0)) {}

	void move();

	World& world;
	glm::vec3 position;
	glm::vec3 size;
	glm::vec3& velocity;
	virtual void setVelocityDelta(float speed) = 0;
	bool gravityON;
	glm::vec3 moveComponent;
	glm::vec3 gravityComponent;
private:
};