#pragma once

#include "cube.h"

class Chunk {
public:
	Chunk(glm::vec3 pos, vector<vector<int>>& heightMap) : position(pos)
	{
		for (int i = 0; i < 6; i++)
		{
			facePositions.push_back(vector<glm::vec3>());
		}

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
		for (int i = 0; i < CHUNK_SIZE; i++)
		{
			for (int j = 0; j < CHUNK_SIZE; j++)
			{
				for (int k = 0; k < CHUNK_SIZE; k++)
				{
					Cube& current = blocks[i][j][k];
					if (current.type == Cube::AIR) continue;
					if (i == 0 || j == 0 || k == 0 || i == CHUNK_SIZE - 1 || j == CHUNK_SIZE - 1 || k == CHUNK_SIZE - 1)
					{
						if (i == 0) drawBlockFace(current, Quad::LEFT);
						if (j == 0) drawBlockFace(current, Quad::BOTTOM);
						if (k == 0) drawBlockFace(current, Quad::FRONT);
						if (i == CHUNK_SIZE - 1) drawBlockFace(current, Quad::RIGHT);
						if (j == CHUNK_SIZE - 1) drawBlockFace(current, Quad::TOP);
						if (k == CHUNK_SIZE - 1) drawBlockFace(current, Quad::BACK);
					}

					if (i == 0)
					{
						if(blocks[i + 1][j][k].type == Cube::AIR) drawBlockFace(current, Quad::RIGHT);
					}
					else if(i == CHUNK_SIZE - 1)
					{
						if(blocks[i - 1][j][k].type == Cube::AIR) drawBlockFace(current, Quad::LEFT);
					}
					else if (blocks[i - 1][j][k].type == Cube::AIR || blocks[i + 1][j][k].type == Cube::AIR)
					{
						if (blocks[i - 1][j][k].type == Cube::AIR) drawBlockFace(current, Quad::LEFT);
						if (blocks[i + 1][j][k].type == Cube::AIR) drawBlockFace(current, Quad::RIGHT);
					}
					if (j == 0)
					{
						if(blocks[i][j + 1][k].type == Cube::AIR) drawBlockFace(current, Quad::TOP);
					}
					else if (j == CHUNK_SIZE - 1)
					{
						if(blocks[i][j - 1][k].type == Cube::AIR) drawBlockFace(current, Quad::BOTTOM);
					}
					else if (blocks[i][j - 1][k].type == Cube::AIR || blocks[i][j + 1][k].type == Cube::AIR)
					{
						if (blocks[i][j - 1][k].type == Cube::AIR) drawBlockFace(current, Quad::BOTTOM);
						if (blocks[i][j + 1][k].type == Cube::AIR) drawBlockFace(current, Quad::TOP);
					}
					if (k == 0)
					{
						if(blocks[i][j][k + 1].type == Cube::AIR) drawBlockFace(current, Quad::BACK);
					}
					else if (k == CHUNK_SIZE - 1)
					{
						if(blocks[i][j][k - 1].type == Cube::AIR) drawBlockFace(current, Quad::FRONT);
					}
					else if (blocks[i][j][k - 1].type == Cube::AIR || blocks[i][j][k + 1].type == Cube::AIR)
					{
						if (blocks[i][j][k - 1].type == Cube::AIR) drawBlockFace(current, Quad::FRONT);
						if (blocks[i][j][k + 1].type == Cube::AIR) drawBlockFace(current, Quad::BACK);	
					}
				}
			}
		}
		for (int i = 0; i < Cube::faces.size(); i++)
		{
			positionBufferIDs.push_back(Cube::faces[i].initPositions(facePositions[i]));
		}
	}

	void getEdgeBlocksX(vector<vector<Cube>>& first, vector<vector<Cube>>& last)
	{
		first = blocks[0];
		last = blocks[CHUNK_SIZE - 1];
	}

	void getEdgeBlocksY(vector<vector<Cube>>& first, vector<vector<Cube>>& last)
	{

	}

	void getEdgeBlocksZ(vector<vector<Cube>>& first, vector<vector<Cube>>& last)
	{

	}

	void drawBlockFace(Cube& block, Quad::Face f)
	{
		facePositions[f].push_back(block.position);
	}

	void setPositions()
	{
		for (int i = 0; i < Cube::faces.size(); i++)
		{
			Cube::faces[i].draw(positionBufferIDs[i]);
		}
	}

	void draw()
	{
		setPositions();
	}
	
	vector<vector<vector<Cube>>> blocks;
	glm::vec3 position;
	vector<Cube> blocksToDraw;
private:
	vector<vector<glm::vec3>> facePositions;
	vector<unsigned int> positionBufferIDs;
};