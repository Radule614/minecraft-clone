#pragma once

#include <vector>
#include <string>
#include <map>

#include "quad.h"

class Cube {
public:
	enum Type {
		AIR = 0,
		DIRT,
		GRASS,
		SAND,
		STONE,
		SNOW
	};
	Type type;
	glm::vec3 position;

	Cube();
	Cube(Type t, glm::vec3 pos);

	void setPosition(glm::vec3& pos);
	static void draw(unsigned int& id);
	static void initiateData();
	static void drawBlocks(std::vector<Cube>& blocks);
	static void drawBlock(Cube& block);
	static std::vector<Quad> faces;
	static std::map<Type, std::vector<glm::vec2>> textureIds;
private:
	static std::vector<glm::vec3> positions;
};

