#pragma once

#include <math.h>
#include "globals.h"

#include "chunk.h"

using namespace global;

class World 
{
public:
    World()
    {
        for (int i = 0; i < CHUNK_SIZE; i++)
        {
            heightMap.push_back(vector<int>());
            for (int j = 0; j < CHUNK_SIZE; j++)
            {
                heightMap[i].push_back(CHUNK_SIZE - 1);
            }
        }
        chunkGenerator();
    }

	void chunkGenerator()
	{
        glm::vec2 cameraPos = glm::vec2(camera.front.x, camera.front.z);
        glm::vec2 pos = glm::vec2(0.0f, 0.0f);
        //cout << glm::distance(cameraPos, glm::vec2(5.0f, 2.0f)) << endl;
        unsigned int radius = 0;
        for (int i = 0; i < 4; i++)
        {
            chunks.push_back(vector<vector<Chunk>>());
            for (int j = 0; j < 2; j++)
            {
                chunks[i].push_back(vector<Chunk>());
                for (int k = 0; k < 4; k++)
                {
                    
                    pos = findAvailablePosition(cameraPos);

                    if (j == 1)
                    {
                        generateHeightMap();
                    }
                    chunks[i][j].push_back(Chunk(glm::vec3(0.0f + i, -2 + j, -0.0f + k), heightMap));
                    chunkPositions.push_back(glm::vec3(0.0f + i, -2 + j, -0.0f + k));
                    heightMapReset();
                }
            }
        }
	}

    void generateHeightMap()
    {
        for (int i = 0; i < CHUNK_SIZE; i++)
        {
            for (int j = 0; j < CHUNK_SIZE; j++)
            {
                heightMap[i][j] = round(3 * sin((i*j)*PI/16.0));
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

    glm::vec3 findAvailablePosition(glm::vec2& cameraPos)
    {
        unsigned int radius = 0;
        

        return glm::vec3();
    }

    //TODO
    void checkChunkEdges(int a, int b, int c)
    {
        Chunk& chunk = chunks[a][b][c];
        vector<vector<Cube>> leftBlocks;
        vector<vector<Cube>> rightBlocks;
        
        chunk.getEdgeBlocksX(leftBlocks, rightBlocks);
        if (a == 0 || b == 0 || c == 0 || a == chunks.size() - 1 || b == chunks[a].size() || c == chunks[a][b].size())
        {
            if (a == 0)
            {
                vector<vector<Cube>>& temp = leftBlocks;
                for (int i = 0; i <temp.size(); i++)
                {
                    for (int j = 0; j < temp[i].size(); j++)
                    {
                        if (temp[i][j].type != Cube::AIR)
                        {
                            chunk.drawBlockFace(temp[i][j], Quad::LEFT);
                        }
                    }
                }
            }

            if (a == chunks.size() - 1)
            {
                vector<vector<Cube>>& temp = rightBlocks;
                for (int i = 0; i < temp.size(); i++)
                {
                    for (int j = 0; j < temp[i].size(); j++)
                    {
                        if (temp[i][j].type != Cube::AIR)
                        {
                            chunk.drawBlockFace(temp[i][j], Quad::RIGHT);
                        }
                    }
                }
            }
        }
    }
    
    void draw()
    {
        for (int i = 0; i < chunks.size(); i++)
        {
            for (int j = 0; j < chunks[i].size(); j++)
            {
                for (int k = 0; k < chunks[i][j].size(); k++)
                {
                    chunks[i][j][k].draw();
                }
            }
        }
    }

private:
    vector<vector<vector<Chunk>>> chunks;
    vector<glm::vec3> chunkPositions;
    vector<vector<int>> heightMap;
};