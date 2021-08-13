#pragma once

using namespace std;

#include "../model/cube.h"

class Chunk {
public:
	Chunk(glm::vec3 pos, vector<vector<int>>& heightMap) : position(pos), frontNeighbor(nullptr), backNeighbor(nullptr), rightNeighbor(nullptr), leftNeighbor(nullptr)
	{
		facePositions.reserve(6);
		faceData.reserve(6);
		for (int i = 0; i < 6; i++)
		{
			facePositions.emplace_back(vector<glm::vec3>());
			faceData.emplace_back(vector<Quad::InstanceData>());
		}

		blocks.reserve(CHUNK_SIZE_X);
		for (int i = 0; i < CHUNK_SIZE_X; i++)
		{
			blocks.emplace_back(vector<vector<Cube>>());
			blocks[i].reserve(CHUNK_SIZE_Y);
			for (int j = 0; j < CHUNK_SIZE_Y; j++)
			{
				blocks[i].emplace_back(vector<Cube>());
				blocks[i][j].reserve(CHUNK_SIZE_Z);
				for (int k = 0; k < CHUNK_SIZE_Z; k++)
				{
					int x, y, z;
					x = 2 * (position.x * CHUNK_SIZE_X + i);
					y = 2 * (position.y * CHUNK_SIZE_Y + j);
					z = 2 * (position.z * CHUNK_SIZE_Z + k);
					blocks[i][j].emplace_back(Cube());
					blocks[i][j][k].position = glm::vec3(x, y, -z);

					if (heightMap[i][k] >= j)
					{
						if (heightMap[i][k]>=80)
						{
							if (heightMap[i][k] >= 100)
							{
								blocks[i][j][k].type = Cube::SNOW;
							}
							else
							{
								blocks[i][j][k].type = Cube::STONE;
							}
						}
						else if(heightMap[i][k] == j)
						{
							blocks[i][j][k].type = Cube::GRASS;
						}
						else if (heightMap[i][k] > j + 2)
						{
							blocks[i][j][k].type = Cube::STONE;
						}
						else {
							blocks[i][j][k].type = Cube::DIRT;
						}
					}
					else
					{
						blocks[i][j][k].type = Cube::AIR;
					}
				}
			}
		}
		determineBlocksToDraw();
		for (int r = 0; r < Cube::faces.size(); r++)
		{
			instanceBufferIDs.push_back(Cube::faces[r].initInstances(faceData[r]));
		}
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
		faceData[f].push_back({ Cube::textureIds[block.type][f], block.position});
	}

	void updatePositions()
	{
		for (int r = 0; r < Cube::faces.size(); r++)
		{
			Cube::faces[r].updateInstanceData(instanceBufferIDs[r], faceData[r]);
		}
	}

	void draw()
	{
		int temp = 0;
		if (instanceBufferIDs.empty()) return;
		for (auto it = Cube::faces.begin(); it != Cube::faces.end(); it++, temp++)
		{
			it->drawInstanced(instanceBufferIDs[temp]);
		}
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
		for (int i = 0; i < faceData.size(); i++)
		{
			faceData[i].clear();
		}
		faceData.clear();

		int temp = 0;
		for (auto it = Cube::faces.begin(); it != Cube::faces.end(); it++, temp++)
		{
			it->clearPositionBuffer(instanceBufferIDs[temp]);
		}
		instanceBufferIDs.clear();
	}

	Cube* getBlock(glm::vec3 pos)
	{
		if (pos.x < 0 || pos.x >CHUNK_SIZE_X - 1 || pos.y < 0 || pos.y > CHUNK_SIZE_Y - 1 || pos.z < 0 || pos.z > CHUNK_SIZE_Z - 1) return nullptr;
		
		return &blocks[pos.x][pos.y][pos.z];
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
	vector<unsigned int> instanceBufferIDs;

	vector<vector<Quad::InstanceData>> faceData;
private:
};