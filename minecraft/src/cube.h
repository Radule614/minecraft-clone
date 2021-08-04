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

	static void draw(unsigned int& id)
	{
		for (int i = 0; i < faces.size(); i++)
		{
			faces[i].draw(id);
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

	static std::vector<Quad> faces;
private:
	static std::vector<glm::vec3> positions;
};

