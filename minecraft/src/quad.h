#pragma once

#include <vector>
#include <string>

#include <GLEW/glew.h>
#include <glm/glm.hpp>

struct Texture {
	unsigned int id;
	std::string path;
};

static std::vector<Texture> loaded_textures;

class Quad {
public:
	enum Face 
	{
		FRONT = 0,
		BACK,
		LEFT,
		RIGHT,
		TOP,
		BOTTOM
	};

	Quad(Face f);

	struct Vertex {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texCoord;
		float textureNumber;
	};

	struct Positions {
		unsigned int id;
		unsigned int size;
	};

	unsigned int VA;
	unsigned int VB;
	unsigned int VE;
	unsigned int instanceVB;

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Positions> positionBuffers;

	void setData(Face& f);
	void setLayout();
	unsigned int initPositions(std::vector<glm::vec3>& positions);
	Positions& findPositions(unsigned int& id);
	void setPositionData(Positions& pos);

	void draw(unsigned int positionsId);

	static glm::vec2 textureCoordinates[4];
	static glm::vec3 getNormal(Face f);
	static void getPositions(Face f, glm::vec3 arr[4]);
};

