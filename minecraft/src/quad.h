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
	Quad(Face f)
	{
		glm::vec3 positions[4];
		getPositions(f, positions);
		glm::vec3 normal = getNormal(f);
		for (int i=0; i<4; i++)
		{
			Vertex temp;
			temp.position.x = positions[i].x;
			temp.position.y = positions[i].y;
			temp.position.z = positions[i].z;
			temp.normal.x = normal.x;
			temp.normal.y = normal.y;
			temp.normal.z = normal.z;
			vertices.push_back(temp);
		}

		glGenVertexArrays(1, &VA);
		glGenBuffers(1, &VB);
		glGenBuffers(1, &VE);

		glBindVertexArray(VA);

		glBindBuffer(GL_ARRAY_BUFFER, VB);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VE);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(offsetof(Vertex, normal)));

		glBindVertexArray(0);
	}

	void draw()
	{
		glBindVertexArray(VA);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
private:
	struct Vertex {
		glm::vec3 position;
		glm::vec3 normal;
	};
	unsigned int VB;
	unsigned int VA;
	unsigned int VE;

	vector<Vertex> vertices;
	unsigned int indices[6] = { 0, 1, 2, 2, 3, 0 };

	glm::vec3 getNormal(Face f)
	{
		switch (f)
		{
		case FRONT:		return	glm::vec3( 0.0f,  0.0f,  1.0f);
		case BACK:		return	glm::vec3( 0.0f,  0.0f, -1.0f);
		case LEFT:		return	glm::vec3(-1.0f,  0.0f,  0.0f);
		case RIGHT:		return	glm::vec3( 1.0f,  0.0f,  0.0f);
		case TOP:		return	glm::vec3( 0.0f,  1.0f,  0.0f);
		case BOTTOM:	return	glm::vec3( 0.0f, -1.0f,  0.0f);
		default:
			break;
		}
	}

	void getPositions(Face f, glm::vec3 arr[4])
	{
		glm::vec3 positions[4];
		switch (f)
		{
		case FRONT:
			positions[0] = glm::vec3(-1.0f, -1.0f,  1.0f);
			positions[1] = glm::vec3(-1.0f,  1.0f,  1.0f);
			positions[2] = glm::vec3( 1.0f,  1.0f,  1.0f);
			positions[3] = glm::vec3( 1.0f, -1.0f,  1.0f);
			break;
		case BACK:
			positions[0] = glm::vec3(-1.0f, -1.0f, -1.0f);
			positions[1] = glm::vec3(-1.0f,  1.0f, -1.0f);
			positions[2] = glm::vec3( 1.0f,  1.0f, -1.0f);
			positions[3] = glm::vec3( 1.0f, -1.0f, -1.0f);
			break;
		case LEFT:
			positions[0] = glm::vec3(-1.0f, -1.0f,  1.0f);
			positions[1] = glm::vec3(-1.0f, -1.0f, -1.0f);
			positions[2] = glm::vec3(-1.0f,  1.0f, -1.0f);
			positions[3] = glm::vec3(-1.0f,  1.0f,  1.0f);
			break;
		case RIGHT:
			positions[0] = glm::vec3( 1.0f, -1.0f,  1.0f);
			positions[1] = glm::vec3( 1.0f, -1.0f, -1.0f);
			positions[2] = glm::vec3( 1.0f,  1.0f, -1.0f);
			positions[3] = glm::vec3( 1.0f,  1.0f,  1.0f);
			break;
		case TOP:
			positions[0] = glm::vec3(-1.0f,  1.0f,  1.0f);
			positions[1] = glm::vec3(-1.0f,  1.0f, -1.0f);
			positions[2] = glm::vec3( 1.0f,  1.0f, -1.0f);
			positions[3] = glm::vec3( 1.0f,  1.0f,  1.0f);
			break;
		case BOTTOM:
			positions[0] = glm::vec3(-1.0f, -1.0f,  1.0f);
			positions[1] = glm::vec3(-1.0f, -1.0f, -1.0f);
			positions[2] = glm::vec3( 1.0f, -1.0f, -1.0f);
			positions[3] = glm::vec3( 1.0f, -1.0f,  1.0f);
			break;
		}
		memcpy(arr, positions, sizeof(positions));
	}
};

//glm::vec2 Quad::textureCoordinates[] = {
//	glm::vec2(0.0f, 0.0f),
//	glm::vec2(1.0f, 0.0f),
//	glm::vec2(0.0f, 1.0f),
//	glm::vec2(1.0f, 1.0f)
//};

