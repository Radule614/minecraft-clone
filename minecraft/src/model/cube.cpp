#include "cube.h"

#include <iostream>

using namespace std;

vector<Quad> Cube::faces = {};
vector<glm::vec3> Cube::positions = {};
map<Cube::Type, vector<glm::vec2>> Cube::textureIds = {
	{Cube::GRASS, {glm::vec2(3, 0), glm::vec2(3, 0), glm::vec2(3, 0), glm::vec2(3, 0), glm::vec2(12, 12), glm::vec2(2, 0)}},
	{Cube::DIRT, {glm::vec2(2, 0), glm::vec2(2, 0), glm::vec2(2, 0), glm::vec2(2, 0), glm::vec2(2, 0), glm::vec2(2, 0)}},
	{Cube::SAND, {glm::vec2(0, 11), glm::vec2(0, 11), glm::vec2(0, 11), glm::vec2(0, 11), glm::vec2(0, 11), glm::vec2(0, 11)}},
	{Cube::STONE, {glm::vec2(1, 0), glm::vec2(1, 0), glm::vec2(1, 0), glm::vec2(1, 0), glm::vec2(1, 0), glm::vec2(1, 0)}},
	{Cube::SNOW, {glm::vec2(2, 4), glm::vec2(2, 4), glm::vec2(2, 4), glm::vec2(2, 4), glm::vec2(2, 4), glm::vec2(2, 4)}}
};

Cube::Cube() {}
Cube::Cube(Type t, glm::vec3 pos)
{
	setPosition(pos);
	this->type = t;
}

void Cube::setPosition(glm::vec3& pos)
{
	position = pos;
}

void Cube::draw(unsigned int& id)
{
	for (int i = 0; i < faces.size(); i++)
	{
		faces[i].drawInstanced(id);
	}
}

void Cube::initiateData()
{
	for (int i = 0; i < 6; i++)
	{
		Quad tmp((Quad::Face)i);
		faces.push_back(tmp);
	}
}

void Cube::drawBlocks(std::vector<Cube>& blocks)
{
	std::vector<Cube>::const_iterator cit;
	for (cit = blocks.begin(); cit != blocks.end(); ++cit)
	{
		positions.push_back(cit->position);
	}
}

void Cube::drawBlock(Cube& block)
{
	positions.push_back(block.position);
}