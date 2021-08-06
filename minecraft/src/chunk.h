#pragma once

#include "cube.h"

class Chunk {
public:
	Chunk(glm::vec3 pos, vector<vector<int>>& heightMap) : position(pos), frontNeighbor(nullptr), backNeighbor(nullptr), rightNeighbor(nullptr), leftNeighbor(nullptr)
	{
		for (int i = 0; i < 6; i++)
		{
			facePositions.push_back(vector<glm::vec3>());
		}

		for (int i = 0; i < CHUNK_SIZE_X; i++)
		{
			blocks.push_back(vector<vector<Cube>>());
			for (int j = 0; j < CHUNK_SIZE_Y; j++)
			{
				blocks[i].push_back(vector<Cube>());
				for (int k = 0; k < CHUNK_SIZE_Z; k++)
				{
					int x, y, z;
					x = 2 * (position.x * CHUNK_SIZE_X + i);
					y = 2 * (position.y * CHUNK_SIZE_Y + j);
					z = 2 * (position.z * CHUNK_SIZE_Z + k);
					blocks[i][j].push_back(Cube());
					blocks[i][j][k].position = glm::vec3(x, y, -z);

					if (heightMap[i][k] >= j)
					{
						blocks[i][j][k].type = Cube::GRASS;
					}
					else
					{
						blocks[i][j][k].type = Cube::AIR;
					}
				}
			}
		}
		determineBlocksToDraw();
	}

	void determineBlocksToDraw()
	{
		for (int i = 0; i < CHUNK_SIZE_X; i++)
		{
			for (int j = 0; j < CHUNK_SIZE_Y; j++)
			{
				for (int k = 0; k < CHUNK_SIZE_Z; k++)
				{
					Cube& current = blocks[i][j][k];
					if (current.type != Cube::AIR) continue;
					if (i == 0)
					{
						if (blocks[i + 1][j][k].type != Cube::AIR) drawBlockFace(blocks[i + 1][j][k], Quad::LEFT);
					}
					else if (i == CHUNK_SIZE_X - 1)
					{
						if (blocks[i - 1][j][k].type != Cube::AIR) drawBlockFace(blocks[i - 1][j][k], Quad::RIGHT);
					}
					else if (blocks[i - 1][j][k].type != Cube::AIR || blocks[i + 1][j][k].type != Cube::AIR)
					{
						if (blocks[i - 1][j][k].type != Cube::AIR) drawBlockFace(blocks[i - 1][j][k], Quad::RIGHT);
						if (blocks[i + 1][j][k].type != Cube::AIR) drawBlockFace(blocks[i + 1][j][k], Quad::LEFT);
					}

					if (j == 0)
					{
						if (blocks[i][j + 1][k].type != Cube::AIR) drawBlockFace(blocks[i][j + 1][k], Quad::BOTTOM);
					}
					else if (j == CHUNK_SIZE_Y - 1)
					{
						if (blocks[i][j - 1][k].type != Cube::AIR) drawBlockFace(blocks[i][j - 1][k], Quad::TOP);
					}
					else if (blocks[i][j - 1][k].type != Cube::AIR || blocks[i][j + 1][k].type != Cube::AIR)
					{
						if (blocks[i][j - 1][k].type != Cube::AIR) drawBlockFace(blocks[i][j - 1][k], Quad::TOP);
						if (blocks[i][j + 1][k].type != Cube::AIR) drawBlockFace(blocks[i][j + 1][k], Quad::BOTTOM);
					}

					if (k == 0)
					{
						if (blocks[i][j][k + 1].type != Cube::AIR) drawBlockFace(blocks[i][j][k + 1], Quad::FRONT);
					}
					else if (k == CHUNK_SIZE_Z - 1)
					{
						if (blocks[i][j][k - 1].type != Cube::AIR) drawBlockFace(blocks[i][j][k - 1], Quad::BACK);
					}
					else if (blocks[i][j][k - 1].type != Cube::AIR || blocks[i][j][k + 1].type != Cube::AIR)
					{
						if (blocks[i][j][k - 1].type != Cube::AIR) drawBlockFace(blocks[i][j][k - 1], Quad::BACK);
						if (blocks[i][j][k + 1].type != Cube::AIR) drawBlockFace(blocks[i][j][k + 1], Quad::FRONT);
					}
				}
			}
		}
	}

	void drawBlockFace(Cube& block, Quad::Face f)
	{
		facePositions[f].push_back(block.position);
	}

	void setPositions()
	{
		int temp = 0;
		for (auto it = Cube::faces.begin(); it != Cube::faces.end(); it++, temp++)
		{
			it->draw(positionBufferIDs[temp]);
		}
	}

	void draw()
	{
		setPositions();
	}

	void clear()
	{
		for (int i = 0; i < blocks.size(); i++)
		{
			for (int j = 0; j < blocks[i].size(); j++)
			{
				blocks[i][j] = vector<Cube>();
			}
			blocks[i] = vector<vector<Cube>>();
		}
		blocks = vector<vector<vector<Cube>>>();
		blocksToDraw.clear();
		for (int i = 0; i < facePositions.size(); i++)
		{
			facePositions[i].clear();
		}
		facePositions.clear();

		int temp = 0;
		for (auto it = Cube::faces.begin(); it != Cube::faces.end(); it++, temp++)
		{
			it->clearPositionBuffer(positionBufferIDs[temp]);
		}
		positionBufferIDs.clear();
	}
	
	vector<vector<vector<Cube>>> blocks;
	glm::vec3 position;
	glm::vec3 gridPosition;
	vector<Cube> blocksToDraw;

	
	Chunk* frontNeighbor;
	Chunk* backNeighbor;
	Chunk* leftNeighbor;
	Chunk* rightNeighbor;
	vector<vector<glm::vec3>> facePositions;
	vector<unsigned int> positionBufferIDs;
private:
};