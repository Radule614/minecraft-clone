#pragma once

#include <vector>
#include <string>

#include "quad.h"

class Cube {
public:
	enum Type {
		AIR = 0,
		DIRT,
		GRASS
	};
	Type type;
	glm::vec3 position;

	Cube() {}
	Cube(Type t, glm::vec3 pos)
	{
		setPosition(pos);
		this->type = t;
	}

	void setPosition(glm::vec3 pos)
	{
		position = pos;
	}

	static void draw()
	{
		for (int i = 0; i < faces.size(); i++)
		{
			faces[i].draw();
		}
	}

	static void initiateData()
	{
		for (int i = 0; i < 6; i++)
		{
			Quad tmp((Quad::Face)i);
			
			faces.push_back(tmp);
		}
	}

	static void drawBlocks(std::vector<Cube>& blocks)
	{
		std::vector<Cube>::const_iterator cit;
		for (cit = blocks.begin(); cit != blocks.end(); ++cit)
		{
			positions.push_back(cit->position);
		}
	}

	static void drawBlock(Cube& block)
	{
		positions.push_back(block.position);
	}

	static void drawBlockFace(Cube& block, Quad::Face f)
	{
		faces[f].positions.push_back(block.position);
	}

	static void setPositions()
	{
		for (int i = 0; i < 6; i++)
		{
			faces[i].setPositions();
		}
	}
private:
	static std::vector<Quad> faces;
	static std::vector<glm::vec3> positions;
};

