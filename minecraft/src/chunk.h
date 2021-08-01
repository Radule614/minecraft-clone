#pragma once

#include "cube.h"

#define CHUNK_SIZE 16

class Chunk {
public:
	Chunk(glm::vec3 pos) : position(pos)
	{
		for (int i = 0; i < CHUNK_SIZE; i++)
		{
			blocks.push_back(vector<vector<Cube>>());
			for (int j = 0; j < CHUNK_SIZE; j++)
			{
				blocks[i].push_back(vector<Cube>());
				for (int k = 0; k < CHUNK_SIZE; k++)
				{
					int x, y, z;
					x = 2 * (position.x * CHUNK_SIZE + i);
					y = 2 * (position.y * CHUNK_SIZE + j);
					z = 2 * (position.z * CHUNK_SIZE + k);
					blocks[i][j].push_back(Cube());
					blocks[i][j][k].type = Cube::GRASS;
					blocks[i][j][k].position = glm::vec3(x, y, -z);
				}
			}
		}
		blocks[0][0][0].type = Cube::AIR;
		blocks[3][3][3].type = Cube::AIR;
		blocks[3][4][3].type = Cube::AIR;
		blocks[4][3][3].type = Cube::AIR;
		blocks[4][4][3].type = Cube::AIR;
		determineBlocksToDraw();
	}

	void determineBlocksToDraw()
	{
		for (int i = 0; i < CHUNK_SIZE; i++)
		{
			for (int j = 0; j < CHUNK_SIZE; j++)
			{
				for (int k = 0; k < CHUNK_SIZE; k++)
				{
					Cube& current = blocks[i][j][k];
					if (current.type == Cube::AIR) continue;
					//if (i == 0 || j == 0 || k == 0 || i == CHUNK_SIZE - 1 || j == CHUNK_SIZE - 1 || k == CHUNK_SIZE - 1) continue;
					if (i == 0 || j == 0 || k == 0 || i == CHUNK_SIZE - 1 || j == CHUNK_SIZE - 1 || k == CHUNK_SIZE - 1)
					{
						if (i == 0) Cube::drawBlockFace(current, Quad::LEFT);
						if (j == 0) Cube::drawBlockFace(current, Quad::BOTTOM);
						if (k == 0) Cube::drawBlockFace(current, Quad::FRONT);
						if (i == CHUNK_SIZE - 1) Cube::drawBlockFace(current, Quad::RIGHT);
						if (j == CHUNK_SIZE - 1) Cube::drawBlockFace(current, Quad::TOP);
						if (k == CHUNK_SIZE - 1) Cube::drawBlockFace(current, Quad::BACK);

						/*if (blocks[1][j][k].type == Cube::AIR) Cube::drawBlockFace(current, Quad::RIGHT);
						if (blocks[i][1][k].type == Cube::AIR) Cube::drawBlockFace(current, Quad::TOP);
						if (blocks[i][j][1].type == Cube::AIR) Cube::drawBlockFace(current, Quad::BACK);
						if (blocks[CHUNK_SIZE - 2][j][k].type == Cube::AIR) Cube::drawBlockFace(current, Quad::LEFT);
						if (blocks[i][CHUNK_SIZE - 2][k].type == Cube::AIR) Cube::drawBlockFace(current, Quad::BOTTOM);
						if (blocks[i][j][CHUNK_SIZE - 2].type == Cube::AIR) Cube::drawBlockFace(current, Quad::TOP);*/

						continue;
					}

					/*if ((i == 0 && blocks[i + 1][j][k].type == Cube::AIR) || (i == CHUNK_SIZE - 1 && blocks[i - 1][j][k].type == Cube::AIR) || (blocks[i - 1][j][k].type == Cube::AIR || blocks[i + 1][j][k].type == Cube::AIR))
					{
						if (i == 0 && blocks[i + 1][j][k].type == Cube::AIR);
						if (i == CHUNK_SIZE - 1 && blocks[i - 1][j][k].type == Cube::AIR);
						if (blocks[i - 1][j][k].type == Cube::AIR || blocks[i + 1][j][k].type == Cube::AIR)Cube::drawBlockFace(current, Quad::RIGHT);
						
					}*/
					

					if (blocks[i - 1][j][k].type == Cube::AIR || blocks[i + 1][j][k].type == Cube::AIR)
					{
						if (blocks[i - 1][j][k].type == Cube::AIR) Cube::drawBlockFace(current, Quad::LEFT);
						if (blocks[i + 1][j][k].type == Cube::AIR) Cube::drawBlockFace(current, Quad::RIGHT);
						continue;
					}
					if (blocks[i][j - 1][k].type == Cube::AIR || blocks[i][j + 1][k].type == Cube::AIR)
					{
						if (blocks[i][j - 1][k].type == Cube::AIR) Cube::drawBlockFace(current, Quad::BOTTOM);
						if (blocks[i][j + 1][k].type == Cube::AIR) Cube::drawBlockFace(current, Quad::TOP);
						continue;
					}
					if (blocks[i][j][k - 1].type == Cube::AIR || blocks[i][j][k + 1].type == Cube::AIR)
					{
						if (blocks[i][j][k - 1].type == Cube::AIR) Cube::drawBlockFace(current, Quad::FRONT);
						if (blocks[i][j][k + 1].type == Cube::AIR) Cube::drawBlockFace(current, Quad::BACK);
						continue;
					}
				}
			}
		}
	}

	static void draw()
	{
		Cube::draw();
	}
	
	vector<vector<vector<Cube>>> blocks;
	glm::vec3 position;
	vector<Cube> blocksToDraw;
private:
};