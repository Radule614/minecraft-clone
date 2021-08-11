#pragma once

#include "GLEW/glew.h"

namespace UI 
{
	unsigned int VB;
	unsigned int VA;
	unsigned int VE;
	float crosshairVertices[20] = {
		-0.001f, -0.001f, -0.1f, 0.0f, 0.0f,
		-0.001f,  0.001f, -0.1f, 0.0f, 1.0f,
		 0.001f,  0.001f, -0.1f, 1.0f, 1.0f,
		 0.001f, -0.001f, -0.1f, 1.0f, 0.0f
	};

	unsigned int crosshairIndices[6] = {
		0, 1, 2,
		2, 3, 0
	};

	void setCrosshair()
	{
		glGenVertexArrays(1, &VA);
		glGenBuffers(1, &VB);
		glGenBuffers(1, &VE);
		
		glBindVertexArray(VA);
		
		glBindBuffer(GL_ARRAY_BUFFER, VB);
		glBufferData(GL_ARRAY_BUFFER, sizeof(crosshairVertices), crosshairVertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VE);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(crosshairIndices), crosshairIndices, GL_STATIC_DRAW);
		
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
		
		glBindVertexArray(0);
	}

	void drawCrosshair()
	{
		glBindVertexArray(VA);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}