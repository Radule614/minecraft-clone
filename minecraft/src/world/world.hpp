#pragma once

#include <math.h>
#include "../utility/perlinNoise.hpp"

#include "../globals.hpp"
#include "chunk.hpp"

using namespace global;

class World 
{
public:
    World(unsigned int seed = 1715) : seed(seed), worldSize(CHUNK_NUMBER), frequency(2), octaves(6)
    {
        noiseGenerator = siv::PerlinNoise(seed);

        for (int i = 0; i < CHUNK_SIZE_X; i++)
        {
            heightMap.push_back(vector<int>());
            for (int j = 0; j < CHUNK_SIZE_Z; j++)
            {
                heightMap[i].push_back(CHUNK_SIZE_Y - 1);
            }
        }
        chunkGenerator();
    }

	void chunkGenerator()
	{   
        glm::vec2 pos;
        unsigned int radius = 0;
        for (int i = 0; i < worldSize; i++)
        {
            chunks.push_back(vector<vector<Chunk*>>());
            chunks[i].push_back(vector<Chunk*>());
            for (int k = 0; k < worldSize; k++)
            {
                pos = glm::vec2(i, k);
                
                generateHeightMap(i, k);
                    
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
        bool chunkChanged = false;
        bool frontChanged = false;
        bool leftChanged = false;
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
                        frontChanged = true;
                    }
                    if (neighbor.type == Cube::AIR && current.type != Cube::AIR)
                    {
                        chunk->drawBlockFace(current, Quad::FRONT);
                        chunkChanged = true;
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
                        leftChanged = true;
                    }
                    if (neighbor.type == Cube::AIR && current.type != Cube::AIR)
                    {
                        chunk->drawBlockFace(current, Quad::LEFT);
                        chunkChanged = true;
                    }
                }
            }
        }
        if (chunkChanged) chunk->updatePositions();
        if (leftChanged && leftNeighbor != nullptr) leftNeighbor->updatePositions();
        if (frontChanged && frontNeighbor != nullptr) frontNeighbor->updatePositions();
    }

    void generateHeightMap(int gridPosX, int gridPosZ)
    {
        int offsetX = (int)(CHUNK_SIZE_X) * gridPosX ;
        int offsetY = (int)(CHUNK_SIZE_Z) * gridPosZ ;

        const double fx = (int)(CHUNK_SIZE_X) * worldSize / frequency;
        const double fy = (int)(CHUNK_SIZE_Z) * worldSize / frequency;

        for (unsigned int x = 0; x < CHUNK_SIZE_X; x++)
        {
            for (unsigned int y = 0; y < CHUNK_SIZE_Z; y++)
            {
                heightMap[x][y] = 25 + (CHUNK_SIZE_Y - 50) * noiseGenerator.accumulatedOctaveNoise2D_0_1((x + offsetX) / fx, (y + offsetY) / fy, octaves);
                if (heightMap[x][y] <= 65)
                {
                    heightMap[x][y] = 25 + (CHUNK_SIZE_Y - 50) * noiseGenerator.accumulatedOctaveNoise2D_0_1((x + offsetX) / fx, (y + offsetY) / fy, 4);
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
                heightMap[i][j] = CHUNK_SIZE_Y - 1;
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

    Chunk* getChunk(glm::vec3& pos)
    {
        if (pos.x < 0 || pos.x > worldSize - 1 || pos.y != -1 || pos.z < 0 || pos.z > worldSize - 1) return nullptr;
        return chunks[pos.x][pos.y + 1][pos.z];
    }

    Cube* getBlock(glm::vec3& blockPosition)
    {
        glm::vec3 chunkPosition = Chunk::getChunkPosition(blockPosition);
        glm::vec3 blockPositionInChunk = Chunk::getBlockPositionInChunk(blockPosition);
        Chunk* chunk = getChunk(chunkPosition);
        
        Cube* block = nullptr;
        if (chunk != nullptr) block = chunk->getBlock(blockPositionInChunk);
        
        return block;
    }

    void removeBlock(Cube* block)
    {
        glm::vec3 blockPosition = block->position / glm::vec3(2);
        glm::vec3 chunkPosition = Chunk::getChunkPosition(blockPosition);
        glm::vec3 blockPositionInChunk = Chunk::getBlockPositionInChunk(blockPosition);
        Chunk* chunk = getChunk(chunkPosition);
        if (chunk == nullptr) return;
        
        chunk->removeBlockFromDraw(block);
        
        vector<glm::vec3> adjacentP;
        adjacentP.push_back(glm::vec3(blockPosition.x, blockPosition.y, blockPosition.z - 1));
        adjacentP.push_back(glm::vec3(blockPosition.x, blockPosition.y, blockPosition.z + 1));
        adjacentP.push_back(glm::vec3(blockPosition.x + 1, blockPosition.y, blockPosition.z));
        adjacentP.push_back(glm::vec3(blockPosition.x - 1, blockPosition.y, blockPosition.z));
        adjacentP.push_back(glm::vec3(blockPosition.x, blockPosition.y - 1, blockPosition.z));
        adjacentP.push_back(glm::vec3(blockPosition.x, blockPosition.y + 1, blockPosition.z));
        
        int s = 0;
        for (auto it = adjacentP.begin(); it != adjacentP.end(); ++it, s++)
        {
            Cube* adjacentBlock = getBlock(*it);
            glm::vec3 adjacentChunkPosition = Chunk::getChunkPosition(*it);
            Chunk* adjacentBlockChunk = getChunk(adjacentChunkPosition);
            if (adjacentBlockChunk == nullptr || adjacentBlock == nullptr)
            {
                cout << "NULL" << endl;
                continue;
            }
            if (adjacentBlock->type == Cube::AIR) continue;

            if (!(adjacentBlockChunk->instanceDataExists(adjacentP[(Quad::Face)s], (Quad::Face)s)))
            {
                adjacentBlockChunk->drawBlockFace(*adjacentBlock, (Quad::Face)s);
                adjacentBlockChunk->updatePositions();
            }
        }
    }

private:
    vector<vector<vector<Chunk*>>> chunks;
    vector<vector<int>> heightMap;

    vector<glm::vec3> chunkPositions;
    glm::vec2 cameraChunkLocation;
    
    siv::PerlinNoise noiseGenerator;
    unsigned int seed;
    unsigned int worldSize;
    double frequency;
    unsigned int octaves;
    
};