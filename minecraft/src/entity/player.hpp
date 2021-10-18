#pragma once

#include "entity.hpp"

class Player : public Entity
{
public:
	Player(glm::vec3 pos, World& world, glm::vec3 size);

	void checkEdgeCollision();
	
	void checkCollision();

	void updatePositions();
	void move();

	void castRay();
private:
	World& world;
	Camera& view = camera;
	glm::vec3 position;
	glm::vec3 oldPosition;
	glm::vec3 blockPosition;
	glm::vec3 blockPositionInChunk;
	glm::vec3 chunkPosition;
};