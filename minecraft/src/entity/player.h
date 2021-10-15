#pragma once

#include "entity.h"

class Player : public Entity
{
public:
	Player(glm::vec3 pos, World& world, glm::vec3 size) : Entity(pos, size), world(world) {}

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
		vector<Cube*> neighbors;
		Cube* block = nullptr;

		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				for (int k = 0; k < 3; ++k)
				{
					if (i == 1 && (j == 1 || j == 2) && k == 1) continue;
					glm::vec3 tempPos = glm::vec3(blockPosition.x + i - 1, blockPosition.y + j - 2, blockPosition.z + k - 1);
					block = world.getBlock(tempPos);
					if (block != nullptr && block->type != Cube::AIR) neighbors.push_back(block);
					
					/*
					* 
					(camera +- 1)  && block
					checkAABBColision();
						
					*/
				}
			}
		}
		cout << neighbors.size() << endl;
		//utility::printVec3(position);
		
		neighbors.clear();
	}

	void updatePositions()
	{
		position = camera.position;
		blockPosition.x = round(position.x / 2);
		blockPosition.y = round(position.y / 2);
		blockPosition.z = round(position.z / 2);
		blockPositionInChunk.x = (int)blockPosition.x % (CHUNK_SIZE_X);
		blockPositionInChunk.y = CHUNK_SIZE_Y - abs((int)blockPosition.y % (CHUNK_SIZE_Y));
		blockPositionInChunk.z = abs((int)blockPosition.z % (CHUNK_SIZE_Z));
		chunkPosition.x = floor(blockPosition.x / CHUNK_SIZE_X);
		chunkPosition.y = floor(blockPosition.y / CHUNK_SIZE_Y);
		chunkPosition.z = -ceil(blockPosition.z / CHUNK_SIZE_Z);
		
	}
	void move()
	{
		map<unsigned int, bool>& keys = global::pressedKeys;
		if (keys[GLFW_KEY_W] || keys[GLFW_KEY_S] || keys[GLFW_KEY_D] || keys[GLFW_KEY_A])
		{
			camera.move(keys);
			updatePositions();
			checkEdgeCollision();
			checkCollision();
		}
	}
private:
	World& world;
	Camera& view = camera;
	glm::vec3 position;
	glm::vec3 oldPosition;
	glm::vec3 blockPosition;
	glm::vec3 blockPositionInChunk;
	glm::vec3 chunkPosition;
};