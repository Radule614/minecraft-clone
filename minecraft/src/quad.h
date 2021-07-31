#pragma once

#include <vector>

#include <GLEW/glew.h>
#include <glm/glm.hpp>

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

	static glm::vec2 textureCoordinates[4];
	
	static glm::vec3 getNormal(Face f);

	static void getPositions(Face f, glm::vec3 arr[4]);
};

