#pragma once

#include <vector>

#include "quad.h"

class Cube {
public:
	Cube()
	{
		for (int i = 0; i < 6; i++)
		{
			Quad face((Quad::Face)i);
			faces.push_back(face);
		}
	}
	void draw() 
	{
		for (int i = 0; i < faces.size(); i++)
		{
			faces[i].draw();
		}
	}
private:
	vector<Quad> faces;
};