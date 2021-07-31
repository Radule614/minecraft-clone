#include "cube.h"

#include <iostream>

unsigned int Cube::VA = 0;
unsigned int Cube::VB = 0;
unsigned int Cube::VE = 0;
unsigned int Cube::instanceVB = 0;

vector<Cube::Vertex> Cube::vertices = {};
vector<unsigned int> Cube::indices = {};
vector<glm::vec3> Cube::positions = {};

void Cube::setData()
{
	unsigned int faceIndices[] = { 0, 1, 2, 2, 3, 0 };
	unsigned int offset = 0;
	for (int i = 0; i < 6; i++)
	{
		unsigned int texture;
		Quad::Face f = (Quad::Face)i;
		if (f == Quad::Face::TOP)
		{
			texture = 0;
		}
		else if (f == Quad::Face::BOTTOM)
		{
			texture = 2;
		}
		else
		{
			texture = 1;
		}
		glm::vec3 vertexPositions[4];
		Quad::getPositions(f, vertexPositions);
		glm::vec3 normal = Quad::getNormal(f);
		for (int j = 0; j < 4; j++)
		{
			Vertex temp;
			temp.position.x = vertexPositions[j].x;
			temp.position.y = vertexPositions[j].y;
			temp.position.z = vertexPositions[j].z;
			temp.normal.x = normal.x;
			temp.normal.y = normal.y;
			temp.normal.z = normal.z;
			temp.texCoord.x = Quad::textureCoordinates[j].x;
			temp.texCoord.y = Quad::textureCoordinates[j].y;
			temp.textureNumber = texture;
			vertices.push_back(temp);
		}
		for (int j = 0; j < 6; j++)
		{
			indices.push_back(faceIndices[j] + offset);
		}
		offset += 4;
	}
}

void Cube::setLayout()
{
	glGenVertexArrays(1, &VA);
	glGenBuffers(1, &VB);
	glGenBuffers(1, &VE);

	glBindVertexArray(VA);

	glBindBuffer(GL_ARRAY_BUFFER, VB);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VE);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, Cube::Vertex::normal)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, Cube::Vertex::texCoord)));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, Cube::Vertex::textureNumber)));

	glBindVertexArray(0);
}

void Cube::setPositions()
{
	glBindVertexArray(VA);

	glGenBuffers(1, &instanceVB);
	glBindBuffer(GL_ARRAY_BUFFER, instanceVB);
	glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(glm::vec3), &positions[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glVertexAttribDivisor(4, 1);
	glBindVertexArray(0);
}

void Cube::draw()
{
	
	glBindVertexArray(VA);
	glDrawElementsInstanced(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0, positions.size());
	glBindVertexArray(0);
}
