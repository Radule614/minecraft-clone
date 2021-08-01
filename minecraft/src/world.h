#pragma once

#include "chunk.h"

class World 
{
public:
    World()
    {
        chunkGenerator();
        
        Cube::setPositions();
    }

	void chunkGenerator()
	{
        for (int i = 0; i < 4; i++)
        {
            chunks.push_back(vector<vector<Chunk>>());
            for (int j = 0; j < 2; j++)
            {
                chunks[i].push_back(vector<Chunk>());
                for (int k = 0; k < 4; k++)
                {
                    chunks[i][j].push_back(Chunk(glm::vec3(0.0f + i, -2 + j, -0.0f + k)));
                }
            }
        }
	}

    void checkChunkEdges()
    {
        for (int i = 0; i < chunks.size(); i++)
        {
            for (int j = 0; j < chunks[i].size(); j++)
            {
                for (int k = 0; k < chunks[i][j].size(); k++)
                {
                    Chunk& chunk = chunks[i][j][k];

                    for (int a = 0; a < CHUNK_SIZE; a++)
                    {
                        for (int b = 0; b < CHUNK_SIZE; b++)
                        {
                            Cube& block = chunk.blocks[a][b][0];
                            //if (block.type = Cube::AIR) continue;
                            if (k != 0)
                            {
                                Cube& temp = chunks[i][j][k - 1].blocks[a][b][0];
                                //if(temp.type == Cube::AIR)
                            }
                        }
                    }

                }
            }
        }
    }
    
    static void draw()
    {
        Chunk::draw();
    }

private:
    vector<vector<vector<Chunk>>> chunks;
};