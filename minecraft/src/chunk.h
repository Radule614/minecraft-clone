#pragma once

#include "cube.h"

#define CHUNK_SIZE 16

class Chunk {
public:
	Chunk(glm::vec3 pos) : position(pos)
	{
		blocks = new Cube**[CHUNK_SIZE];
		
		for (int i = 0; i < CHUNK_SIZE; i++)
		{
			blocks[i] = new Cube*[CHUNK_SIZE];
			for (int j = 0; j < CHUNK_SIZE; j++)
			{
				blocks[i][j] = new Cube[CHUNK_SIZE];
			}
		}

		for (int i = 0; i < CHUNK_SIZE; i++)
		{
			for (int j = 0; j < CHUNK_SIZE; j++)
			{
				for (int k = 0; k < CHUNK_SIZE; k++)
				{
					int x, y, z;
					x = 2 * (position.x * CHUNK_SIZE + i);
					y = 2 * (position.y * CHUNK_SIZE + j);
					z = 2 * (position.z * CHUNK_SIZE + k);
					blocks[i][j][k].type = Cube::GRASS;
					blocks[i][j][k].position = glm::vec3(x, y, -z);
				}
			}
		}
		determineBlocksToDraw();
	}

	/*~Chunk() {
		for (int i = 0; i < CHUNK_SIZE; i++)
		{
			for (int j = 0; j < CHUNK_SIZE; j++)
			{
				delete[] this->blocks[i][j];
			}
			delete[] this->blocks[i];
		}
		delete[] this->blocks;
	}*/
	
private:
	Cube*** blocks;
	glm::vec3 position;
	vector<Cube> blocksToDraw;

	void determineBlocksToDraw()
	{
		for (int i = 0; i < CHUNK_SIZE; i++)
		{
			for (int j = 0; j < CHUNK_SIZE; j++)
			{
				for (int k = 0; k < CHUNK_SIZE; k++)
				{
					if (blocks[i][j][k].type == Cube::AIR) continue;
					if (i == 0 || j == 0 || k == 0 || i == CHUNK_SIZE - 1 || j == CHUNK_SIZE - 1 || k == CHUNK_SIZE - 1)
					{
						blocksToDraw.push_back(blocks[i][j][k]);
						Cube::positions.push_back(blocks[i][j][k].position);
						continue;
					}
					if (blocks[i - 1][j][k].type == Cube::AIR || blocks[i + 1][j][k].type == Cube::AIR)
					{
						blocksToDraw.push_back(blocks[i][j][k]);
						Cube::positions.push_back(blocks[i][j][k].position);
						continue;
					}
					if (blocks[i][j - 1][k].type == Cube::AIR || blocks[i][j + 1][k].type == Cube::AIR)
					{
						blocksToDraw.push_back(blocks[i][j][k]);
						Cube::positions.push_back(blocks[i][j][k].position);
						continue;
					}
					if (blocks[i][j][k - 1].type == Cube::AIR || blocks[i][j][k + 1].type == Cube::AIR)
					{
						blocksToDraw.push_back(blocks[i][j][k]);
						Cube::positions.push_back(blocks[i][j][k].position);
						continue;
					}
				}
			}
		}
	}
};