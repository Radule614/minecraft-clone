#pragma once

#include <vector>
#include <string>
#include <iostream>

#include <GLEW/glew.h>
#include <glm/glm.hpp>

#define ATLAS_SIZE 768
#define TEXTURE_SIZE 48

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
	};

	struct Instance {
		unsigned int id;
		unsigned int size;
	};

	struct InstanceData {
		glm::vec2 faceTexture;
		glm::vec3 facePosition;
	};

	unsigned int VA;
	unsigned int VB;
	unsigned int VE;
	unsigned int instanceVB;

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Instance> instances;

	void setData(Face& f);
	void setLayout();
	Instance& findInstace(unsigned int& id);
	void clearPositionBuffer(unsigned int& id);
	void bindInstanceData(Instance& pos);
	unsigned int initInstances(std::vector<InstanceData>& positions);
	void updateInstanceData(unsigned int& id, std::vector<InstanceData>& positions);
	void setInstanceLayout();

	void drawInstanced(unsigned int positionsId);

	static glm::vec2 textureCoordinates[4];
	static glm::vec3 getNormal(Face f);
	static void getPositions(Face f, glm::vec3 arr[4]);
};