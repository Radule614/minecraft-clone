#pragma once

#include "entity.hpp"

class Player : public Entity
{
public:
	Player(World& w, glm::vec3 pos, glm::vec3 size, bool gravityON = false) : Entity(w, pos, size, camera.velocity, gravityON), view(camera)
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
		glm::vec3& v = velocity;
		std::vector<std::pair<Cube *, float>> z;
		glm::vec3 contact_point;
		glm::vec3 contact_normal;
		float contact_time;

		for (int i = 0; i < 3; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				for (int k = 0; k < 3; ++k)
				{
					glm::vec3 tempPos = glm::vec3(blockPosition.x + i - 1, blockPosition.y + j - 2, blockPosition.z + k - 1);
					block = world.getBlock(tempPos);
					if (block != nullptr && block->type != Cube::AIR)
					{
						if (ray::dynamicCuboidCollision({ position - glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.5, 1.8, 0.5), v}, {block->position, glm::vec3(1, 1, 1)}, contact_point, contact_normal, contact_time))
						{
							z.push_back({block, contact_time});
						}
					}
				}
			}
		}
		std::sort(z.begin(), z.end(), [](const std::pair<Cube*, float>& a, const std::pair<Cube*, float>& b) {return a.second < b.second; });
		for (auto j : z)
		{
			if (ray::dynamicCuboidCollision({ position - glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.5, 1.8, 0.5), v }, { j.first->position, glm::vec3(1, 1, 1) }, contact_point, contact_normal, contact_time))
			{
				{
					v += contact_normal * glm::vec3(abs(v.x), abs(v.y), abs(v.z)) * (1.0f - contact_time);
					if (contact_normal.y == 1.0f)
					{
						if (pressedKeys[GLFW_KEY_SPACE])
						{
							gravityComponent = glm::vec3(0.0f, 0.7f, 0.0f);
						}
						else
						{
							gravityComponent = glm::vec3(0);
						}
					}
					else if (contact_normal.y == -1.0f && gravityComponent.y > 0.0f)
					{
						gravityComponent = glm::vec3(0.0f);
						v.y = 0.0f;
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
		blockPositionInChunk = Chunk::getBlockPositionInChunk(blockPosition);
		chunkPosition = Chunk::getChunkPosition(blockPosition);
	}

	void setVelocityDelta(float speed)
	{
		view.speed = speed;
	}

	void move()
	{
		map<unsigned int, bool>& keys = global::pressedKeys;
		if (keys[GLFW_KEY_W] || keys[GLFW_KEY_S] || keys[GLFW_KEY_D] || keys[GLFW_KEY_A])
		{
			moveComponent = view.calculateMoveDirection(keys);
		}
		else
		{
			moveComponent = glm::vec3(0);
		}
		velocity = moveComponent + gravityComponent;
		checkCollision();
		view.setVelocity(velocity);
		view.move();
		updatePositions();
		checkEdgeCollision();
	}

	void castRay(long long time)
	{
		if (time - destroyedBlockTime < blockDestroyCooldown) return;

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
									destroyedBlockTime = time;
									utility::print2Vec3(blockPosition, tempPos);
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
	Camera& view;
	glm::vec3 position;
	glm::vec3 oldPosition;
	glm::vec3 blockPosition;
	glm::vec3 blockPositionInChunk;
	glm::vec3 chunkPosition;

	int blockDestroyCooldown = 100;
	long long destroyedBlockTime;
};