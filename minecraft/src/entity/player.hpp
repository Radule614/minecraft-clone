#pragma once

#include "entity.hpp"

class Player : public Entity
{
public:
	Player(glm::vec3 pos, World& world, glm::vec3 size) : Entity(pos, size), world(world), view(camera) {}

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
			view.position.x = 0;
		}
		if (chunkPosition.y == -2)
		{
			chunkPosition.y = -1;
			view.position.y = -(2 * CHUNK_SIZE_Y - 1);
		}
		if (chunkPosition.z == -1)
		{
			chunkPosition.z = 0;
			view.position.z = 0;
		}
	}
	
	void checkCollision()
	{
		Cube* block = nullptr;

		float Axmin, Axmax, Aymin, Aymax, Azmin, Azmax;
		float Bxmin, Bxmax, Bymin, Bymax, Bzmin, Bzmax;

		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				for (int k = 0; k < 3; ++k)
				{
					if (i == 1 && (j == 1 || j == 2) && k == 1) continue;
					glm::vec3 tempPos = glm::vec3(blockPosition.x + i - 1, blockPosition.y + j - 2, blockPosition.z + k - 1);
					block = world.getBlock(tempPos);
					if (block != nullptr && block->type != Cube::AIR)
					{
						/*Axmin = position.x - 1;
						Axmax = position.x + 1;
						Aymin = position.y - 3;
						Aymax = position.y + 1;
						Azmin = position.z - 1;
						Azmax = position.z + 1;

						Bxmin = block->position.x - 1;
						Bxmax = block->position.x + 1;
						Bymin = block->position.y - 1;
						Bymax = block->position.y + 1;
						Bzmin = block->position.z - 1;
						Bzmax = block->position.z + 1;

						if ((Axmax > Bxmin && Bxmax > Axmin) && (Aymax > Bymin && Bymax > Aymin) && (Azmax > Bzmin && Bzmax > Azmin))
						{
							view.position.y = camera.oldPosition.y;
						}*/

						glm::vec3 direction = position - oldPosition;
						glm::vec3 contact_point;
						glm::vec3 contact_normal;
						float t_hit_near;
						if (ray::cubeCollision(oldPosition, direction, block, contact_point, contact_normal, t_hit_near)) cout << "collision" << endl;
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
			camera.move(keys);
			updatePositions();
			checkEdgeCollision();
			checkCollision();
		}
	}

	void castRay()
	{
		Cube* block = nullptr;
		glm::vec3& direction = view.front;
		for (int i = 0; i < 9; ++i)
		{
			for (int j = 0; j < 9; ++j)
			{
				for (int k = 0; k < 9; ++k)
				{
					glm::vec3 tempPos = glm::vec3(blockPosition.x + i - 4, blockPosition.y + j - 4, blockPosition.z + k - 4);
					block = world.getBlock(tempPos);
					if (block != nullptr && block->type != Cube::AIR)
					{
						glm::vec3 contact_point;
						glm::vec3 contact_normal;
						float t_hit_near;
						if (ray::cubeCollision(position, direction, block, contact_point, contact_normal, t_hit_near))
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
private:
	World& world;
	Camera& view;
	glm::vec3 position;
	glm::vec3 oldPosition;
	glm::vec3 blockPosition;
	glm::vec3 blockPositionInChunk;
	glm::vec3 chunkPosition;
};