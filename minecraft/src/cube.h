#pragma once

#include <vector>
#include <string>

#include "quad.h"

using namespace std;

struct Texture {
	unsigned int id;
	string path;
};

static vector<Texture> loaded_textures;

class Cube {
public:
	enum Type {
		AIR = 0,
		DIRT,
		GRASS
	};

	struct Vertex {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texCoord;
		float textureNumber;
	};

	Type type;
	glm::vec3 position;

	static unsigned int VA;
	static unsigned int VB;
	static unsigned int VE;
	static unsigned int instanceVB;

	static vector<Vertex> vertices;
	static vector<unsigned int> indices;
	static vector<glm::vec3> positions;

	Cube() {}
	Cube(Type t)
	{
		this->type = t;
	}

	static void setData();
	static void setLayout();
	
	static void setPositions();
	static void draw();
private:
	
};

