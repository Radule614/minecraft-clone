#pragma once

#include "entity.h"

class Player : public Entity
{
public:
	Player(glm::vec3 pos) : Entity(pos) {}

	void checkEdgeCollision()
	{
		if (chunkPosition.x == CHUNK_NUMBER)
		{
			chunkPosition.x = CHUNK_NUMBER - 1;
			camera.position.x = CHUNK_NUMBER * CHUNK_SIZE_X * 2 - 1;
		}
		if (chunkPosition.y == 0)
		{
			chunkPosition.y = -1;
			camera.position.y = -1;
		}
		if (chunkPosition.z == CHUNK_NUMBER)
		{
			chunkPosition.z = CHUNK_NUMBER - 1;
			camera.position.z = -(CHUNK_NUMBER * CHUNK_SIZE_Z * 2 - 1);
		}
		if (chunkPosition.x == -1)
		{
			chunkPosition.x = 0;
			camera.position.x = 0;
		}
		if (chunkPosition.y == -2)
		{
			chunkPosition.y = -1;
			camera.position.y = -(2 * CHUNK_SIZE_Y - 1);
		}
		if (chunkPosition.z == -1)
		{
			chunkPosition.z = 0;
			camera.position.z = 0;
		}
	}

	void checkCollision()
	{

	}

	void move()
	{
		map<unsigned int, bool>& keys = global::pressedKeys;
		if (keys[GLFW_KEY_W] || keys[GLFW_KEY_S] || keys[GLFW_KEY_D] || keys[GLFW_KEY_A])
		{
			camera.move(keys);
			chunkPosition.x = (int)(floor(camera.position.x / CHUNK_SIZE_X / 2));
			chunkPosition.y = (int)(floor(camera.position.y / CHUNK_SIZE_Y / 2));
			chunkPosition.z = (int)(-ceil(camera.position.z / CHUNK_SIZE_Z / 2));
			cout << "(" << chunkPosition.x << ", " << chunkPosition.y << ", " << chunkPosition.z << ")" << endl;
			checkEdgeCollision();
		}
	}
private:
	Camera& view = camera;
	glm::vec3 chunkPosition;
	glm::vec3 blockPosition;
};