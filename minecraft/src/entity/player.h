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
		Chunk* chunk = world.getChunk(chunkPosition);
		Chunk* frontChunk = chunk->frontNeighbor;
		Chunk* backChunk = chunk->backNeighbor;
		Chunk* rightChunk = chunk->rightNeighbor;
		Chunk* leftChunk = chunk->leftNeighbor;

		glm::vec3& pos = blockPositionInChunk;
		Cube* block = chunk->getBlock(pos);
		Cube* bottom = chunk->getBlock(glm::vec3(pos.x, pos.y - 1, pos.z));
		Cube* front;
		Cube* back;
		Cube* left;
		Cube* right;

		back = chunk->getBlock(glm::vec3(pos.x, pos.y, pos.z + 1));
		if (back == nullptr && backChunk != nullptr)
		{
			back = backChunk->getBlock(glm::vec3(pos.x, pos.y, 0));
		}

		front = chunk->getBlock(glm::vec3(pos.x, pos.y, pos.z - 1));
		if (front == nullptr && frontChunk != nullptr)
		{
			front = frontChunk->getBlock(glm::vec3(pos.x, pos.y, CHUNK_SIZE_Z - 1));
		}

		left = chunk->getBlock(glm::vec3(pos.x - 1, pos.y, pos.z));
		if (left == nullptr && leftChunk != nullptr)
		{
			left = leftChunk->getBlock(glm::vec3(CHUNK_SIZE_X - 1, pos.y, pos.z));
		}

		right = chunk->getBlock(glm::vec3(pos.x + 1, pos.y, pos.z));
		if (right == nullptr && rightChunk != nullptr)
		{
			right = rightChunk->getBlock(glm::vec3(0, pos.y, pos.z));
		}

		if (block != nullptr)
		{
			
			if (bottom != nullptr && bottom->type != Cube::AIR)
			{
			
				if (abs(camera.position.y - bottom->position.y) < 2)
				{
					camera.position.y = block->position.y;
					updatePositions();
					cout << "collision-bottom" << endl;
				}
			}
			if (back != nullptr && back->type != Cube::AIR)
			{
				if (abs(camera.position.z - back->position.z) < 2)
				{
					camera.position.z = block->position.z;
					updatePositions();
					cout << "collision-back" << endl;
				}
			}
			if (front != nullptr && front->type != Cube::AIR)
			{
				if (abs(camera.position.z - front->position.z) < 2)
				{
					camera.position.z = block->position.z;
					updatePositions();
					cout << "collision-front" << endl;
				}
			}

			if (left != nullptr && left->type != Cube::AIR)
			{
				if (abs(camera.position.x - left->position.x) < 2)
				{
					camera.position.x = block->position.x;
					updatePositions();
					cout << "collision-left" << endl;
				}
			}
			if (right != nullptr && right->type != Cube::AIR)
			{
				if (abs(camera.position.x - right->position.x) < 2)
				{
					camera.position.x = block->position.x;
					updatePositions();
					cout << "collision-right" << endl;
				}
			}
		}
		else 
		{
			cout << "BLOCK NULL" << endl;
		}
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