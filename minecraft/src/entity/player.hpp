#pragma once

#include "entity.hpp"

class Player : public Entity
{
public:
	Player(glm::vec3 pos, World& world, glm::vec3 size) : Entity(pos, size), world(world), view(camera) 
	{
		updatePositions();
	}

	void checkEdgeCollision()
	{
		if (chunkPosition.x == CHUNK_NUMBER)
		{
			chunkPosition.x = CHUNK_NUMBER - 1;
			view.position.x = CHUNK_NUMBER * CHUNK_SIZE_X * 2 - 1;
		}
		if (chunkPosition.y == 0)
		{
			chunkPosition.y = -1;
			view.position.y = -1;
		}
		if (chunkPosition.z == CHUNK_NUMBER)
		{
			chunkPosition.z = CHUNK_NUMBER - 1;
			view.position.z = -(CHUNK_NUMBER * CHUNK_SIZE_Z * 2 - 1);
		}
		if (chunkPosition.x == -1)
		{
			chunkPosition.x = 0;
			view.position.x = -1;
		}
		if (chunkPosition.y == -2)
		{
			chunkPosition.y = -1;
			view.position.y = -(2 * CHUNK_SIZE_Y + 1);
		}
		if (chunkPosition.z == -1)
		{
			chunkPosition.z = 0;
			view.position.z = 1;
		}
	}
	
	void checkCollision()
	{
		Cube* block = nullptr;

		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				for (int k = 0; k < 3; ++k)
				{
					//if (i == 1 && (j == 1 || j == 2) && k == 1) continue;
					glm::vec3 tempPos = glm::vec3(blockPosition.x + i - 1, blockPosition.y + j - 2, blockPosition.z + k - 1);
					block = world.getBlock(tempPos);
					if (block != nullptr && block->type != Cube::AIR)
					{

						//glm::vec3 direction = position - oldPosition;
						glm::vec3 direction = view.direction;
						glm::vec3 contact_point;
						glm::vec3 contact_normal;
						float t_hit_near;
						if (ray::cuboidCollision(position, direction, {position, glm::vec3(1, 1, 1)}, contact_point, contact_normal, t_hit_near))
						{
							
							utility::printVec3(contact_normal);
							//view.position += contact_normal;
							//view.velocity.x = 0;
							//view.velocity.y = 0;
							//view.velocity.z = 0;
						}
					}
				}
			}
		}
	}

	void updatePositions()
	{
		oldPosition = position;
		position = view.position;
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
			
			camera.calculateVelocity(keys);
			
			checkCollision();
			
			camera.move();
			updatePositions();
			
			
			checkEdgeCollision();
		}
	}

	void castRay()
	{
		Cube* block = nullptr;
		glm::vec3& direction = view.front;

		int radius = 6;

		for (int r = 0; r <= radius; ++r)
		{
			for (int i = -r; i <= r; ++i)
			{
				for (int j = -r; j <= r; ++j)
				{
					for (int k = -r; k <= r; ++k)
					{
						glm::vec3 tempPos = glm::vec3(blockPosition.x + i, blockPosition.y + j, blockPosition.z + k);
						block = world.getBlock(tempPos);
						if (block != nullptr && block->type != Cube::AIR)
						{
							glm::vec3 contact_point;
							glm::vec3 contact_normal;
							float t_hit_near;
							if (ray::cuboidCollision(position, direction, { block->position, glm::vec3(1, 1, 1) }, contact_point, contact_normal, t_hit_near))
							{
								float d = glm::distance(position, contact_point);
								if (d <= 9)
								{
									world.removeBlock(block);
									return;
								}
							}
						}
					}
				}
			}
		}
	}
private:
	World& world;
	Camera& view;
	glm::vec3 position;
	glm::vec3 oldPosition;
	glm::vec3 blockPosition;
	glm::vec3 blockPositionInChunk;
	glm::vec3 chunkPosition;
};