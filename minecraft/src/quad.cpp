#include "quad.h"

using namespace std;

Quad::Quad(Face f)
{
	setData(f);
	setLayout();

	glGenBuffers(1, &instanceVB);
}

glm::vec2 Quad::textureCoordinates[4] = {
	glm::vec2(0.0f, 0.0f),
	glm::vec2(0.0f, 1.0f),
	glm::vec2(1.0f, 1.0f),
	glm::vec2(1.0f, 0.0f)
};

glm::vec3 Quad::getNormal(Face f)
{
	switch (f)
	{
	case FRONT:		return	glm::vec3(0.0f, 0.0f, 1.0f);
	case BACK:		return	glm::vec3(0.0f, 0.0f, -1.0f);
	case LEFT:		return	glm::vec3(-1.0f, 0.0f, 0.0f);
	case RIGHT:		return	glm::vec3(1.0f, 0.0f, 0.0f);
	case TOP:		return	glm::vec3(0.0f, 1.0f, 0.0f);
	case BOTTOM:	return	glm::vec3(0.0f, -1.0f, 0.0f);
	default:
		break;
	}
}

void Quad::getPositions(Face f, glm::vec3 arr[4])
{
	glm::vec3 positions[4];
	switch (f)
	{
	case FRONT:
		positions[0] = glm::vec3(-1.0f, -1.0f, 1.0f);
		positions[1] = glm::vec3(-1.0f, 1.0f, 1.0f);
		positions[2] = glm::vec3(1.0f, 1.0f, 1.0f);
		positions[3] = glm::vec3(1.0f, -1.0f, 1.0f);
		break;
	case BACK:
		positions[0] = glm::vec3(-1.0f, -1.0f, -1.0f);
		positions[1] = glm::vec3(-1.0f, 1.0f, -1.0f);
		positions[2] = glm::vec3(1.0f, 1.0f, -1.0f);
		positions[3] = glm::vec3(1.0f, -1.0f, -1.0f);
		break;
	case LEFT:
		positions[0] = glm::vec3(-1.0f, -1.0f, -1.0f);
		positions[1] = glm::vec3(-1.0f, 1.0f, -1.0f);
		positions[2] = glm::vec3(-1.0f, 1.0f, 1.0f);
		positions[3] = glm::vec3(-1.0f, -1.0f, 1.0f);
		break;
	case RIGHT:
		positions[0] = glm::vec3(1.0f, -1.0f, 1.0f);
		positions[1] = glm::vec3(1.0f, 1.0f, 1.0f);
		positions[2] = glm::vec3(1.0f, 1.0f, -1.0f);
		positions[3] = glm::vec3(1.0f, -1.0f, -1.0f);
		break;
	case TOP:
		positions[0] = glm::vec3(-1.0f, 1.0f, 1.0f);
		positions[1] = glm::vec3(-1.0f, 1.0f, -1.0f);
		positions[2] = glm::vec3(1.0f, 1.0f, -1.0f);
		positions[3] = glm::vec3(1.0f, 1.0f, 1.0f);
		break;
	case BOTTOM:
		positions[0] = glm::vec3(-1.0f, -1.0f, 1.0f);
		positions[1] = glm::vec3(-1.0f, -1.0f, -1.0f);
		positions[2] = glm::vec3(1.0f, -1.0f, -1.0f);
		positions[3] = glm::vec3(1.0f, -1.0f, 1.0f);
		break;
	}
	memcpy(arr, positions, sizeof(positions));
}

void Quad::setData(Face f)
{
	indices.clear();
	vertices.clear();
	unsigned int faceIndices[] = { 0, 1, 2, 2, 3, 0 };
	unsigned int offset = 0;
	unsigned int texture;
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
		indices.push_back(faceIndices[j]);
	}
}

void Quad::setLayout()
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
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, Quad::Vertex::normal)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, Quad::Vertex::texCoord)));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, Quad::Vertex::textureNumber)));

	glBindVertexArray(0);
}

void Quad::setPositions()
{
	if (positions.size() == 0) return;

	glBindVertexArray(VA);
	
	glBindBuffer(GL_ARRAY_BUFFER, instanceVB);
	glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(glm::vec3), &positions[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glVertexAttribDivisor(4, 1);
	glBindVertexArray(0);
}

void Quad::draw()
{
	glBindVertexArray(VA);
	glDrawElementsInstanced(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0, positions.size());
	glBindVertexArray(0);
}