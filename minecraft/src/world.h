#pragma once

#include <math.h>
#include <list>

#include "globals.h"

#include "chunk.h"

using namespace global;

class World 
{
public:
    World()
    {
        for (int i = 0; i < CHUNK_SIZE_X; i++)
        {
            heightMap.push_back(vector<int>());
            for (int j = 0; j < CHUNK_SIZE_Z; j++)
            {
                heightMap[i].push_back(CHUNK_SIZE_Y - 1);
            }
        }
        chunkGenerator();

        for (int i = 0; i < chunks.size(); i++)
        {
            for (int j = 0; j < chunks[i].size(); j++)
            {
                for (int k = 0; k < chunks[i][j].size(); k++)
                {
                    for (int r = 0; r < Cube::faces.size(); r++)
                    {
                        Chunk& chunk = *chunks[i][j][k];
                        chunk.positionBufferIDs.push_back(Cube::faces[r].initPositions(chunk.facePositions[r]));
                    }
                }
            }
        }
    }

	void chunkGenerator()
	{   
        glm::vec2 pos;
        unsigned int radius = 0;
        for (int i = 0; i < 10; i++)
        {
            chunks.push_back(vector<vector<Chunk*>>());
            chunks[i].push_back(vector<Chunk*>());
            for (int k = 0; k < 10; k++)
            {
                pos = glm::vec2(i, k);
                    
                    
                if(i==3 && k==3) generateHeightMap(40);
                else generateHeightMap();
                    
                chunks[i][0].push_back(new Chunk(glm::vec3(pos.x, -1, pos.y), heightMap));
                chunks[i][0][k]->gridPosition = glm::vec3(i, 0, k);
                chunkPositions.push_back(glm::vec3(pos.x, -1, pos.y));
                    
                if (i != 0 && k != 0)
                {
                    chunks[i][0][k]->frontNeighbor = chunks[i][0][k - 1];
                    chunks[i][0][k - 1]->backNeighbor = chunks[i][0][k];
                    chunks[i][0][k]->leftNeighbor = chunks[i - 1][0][k];
                    chunks[i - 1][0][k]->rightNeighbor = chunks[i][0][k];
                }
                else if (i != 0)
                {
                    chunks[i][0][k]->frontNeighbor = nullptr;
                    chunks[i][0][k]->leftNeighbor = chunks[i - 1][0][k];
                    chunks[i - 1][0][k]->rightNeighbor = chunks[i][0][k];
                }
                else if (k != 0)
                {
                    chunks[i][0][k]->frontNeighbor = chunks[i][0][k - 1];
                    chunks[i][0][k - 1]->backNeighbor = chunks[i][0][k];
                    chunks[i][0][k]->leftNeighbor = nullptr;
                }
                else
                {
                    chunks[i][0][k]->frontNeighbor = nullptr;
                    chunks[i][0][k]->leftNeighbor = nullptr;
                }
                checkChunkEdges(chunks[i][0][k]);
                heightMapReset();
            }
        }
	}

    void checkChunkEdges(Chunk* chunk)
    {
        Chunk* frontNeighbor = chunk->frontNeighbor;
        Chunk* leftNeighbor = chunk->leftNeighbor;
        for (int i = 0; i < CHUNK_SIZE_X; i++)
        {
            for (int j = 0; j < CHUNK_SIZE_Y; j++)
            {
                Cube& current = chunk->blocks[i][j][0];

                if (frontNeighbor != nullptr)
                {
                    Cube& neighbor = frontNeighbor->blocks[i][j][CHUNK_SIZE_Z - 1];
                    if (current.type == Cube::AIR && neighbor.type != Cube::AIR)
                    {
                        frontNeighbor->drawBlockFace(neighbor, Quad::BACK);
                    }
                    if (neighbor.type == Cube::AIR && current.type != Cube::AIR)
                    {
                        chunk->drawBlockFace(current, Quad::FRONT);
                    }
                }
            }
        }

        for (int i = 0; i < CHUNK_SIZE_Y; i++)
        {
            for (int j = 0; j < CHUNK_SIZE_Z; j++)
            {
                Cube& current = chunk->blocks[0][i][j];
                if (leftNeighbor != nullptr)
                {
                    Cube& neighbor = leftNeighbor->blocks[CHUNK_SIZE_X - 1][i][j];
                    if (current.type == Cube::AIR && neighbor.type != Cube::AIR)
                    {
                        leftNeighbor->drawBlockFace(neighbor, Quad::RIGHT);

                    }
                    if (neighbor.type == Cube::AIR && current.type != Cube::AIR)
                    {
                        chunk->drawBlockFace(current, Quad::LEFT);
                    }
                }
            }
        }
    }

    void generateHeightMap(int h = -1)
    {
        for (int i = 0; i < CHUNK_SIZE_X; i++)
        {
            for (int j = 0; j < CHUNK_SIZE_Z; j++)
            {
                if (h != -1)
                {
                    heightMap[i][j] = h;
                }
                else
                {
                    heightMap[i][j] = 5 + 2 *sin((i * j));
                }
            }
        }
    }

    void heightMapReset()
    {
        for (int i = 0; i < heightMap.size(); i++)
        {
            for (int j = 0; j < heightMap.size(); j++)
            {
                heightMap[i][j] = 15;
            }
        }
    }

    bool chunkExists(glm::vec2& pos)
    {
        for (auto it = chunkPositions.begin(); it != chunkPositions.end(); it++)
        {
            if (pos.x == it->x && pos.y == it->z) return true;
        }
        return false;
    }

    glm::vec2 findAvailablePosition()
    {
        glm::vec2& cameraPos = cameraChunkLocation;
        glm::vec2 temp;
        int radius = 0;
        while (radius != CHUNK_SPAWN_RADIUS + 1)
        {
            for (int i = -radius; i <= radius; i++)
            {
                for (int j = -radius; j <= radius; j++)
                {
                    temp = glm::vec2(cameraPos.x + i, (cameraPos.y - j));
                    if (!chunkExists(temp)) return temp;
                }
            }
            radius++;
        }
        return glm::vec2();
    }
    
    void draw()
    {
        for (int i = 0; i < chunks.size(); i++)
        {
            for (int j = 0; j < chunks[i].size(); j++)
            {
                for (int k = 0; k < chunks[i][j].size(); k++)
                {
                    chunks[i][j][k]->draw();
                }
            }
        }
    }

private:
    vector<vector<vector<Chunk*>>> chunks;
    vector<vector<int>> heightMap;

    vector<glm::vec3> chunkPositions;
    glm::vec2 cameraChunkLocation;
};