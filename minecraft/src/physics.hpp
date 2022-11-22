#pragma once

#include <vector>
#include <chrono>

#include "utility/utility.hpp"
#include "entity/player.hpp"

typedef std::chrono::high_resolution_clock::time_point type_hrc_t;
typedef std::chrono::high_resolution_clock::duration type_hrc_d;

std::chrono::high_resolution_clock hrc;
type_hrc_t start = hrc.now();

class Physics {
public:
	Physics() : counter(0), velocityModifier(20)
	{
		
	}

	void pushEntity(Entity* entity)
	{
		entities.push_back(entity);
	}

	void updateGravity()
	{
		vector<Entity*>::const_iterator cit;
		for (cit = entities.begin(); cit != entities.end(); ++cit)
		{
			Entity& temp = *(*cit);
				
			temp.setVelocityDelta(this->velocityModifier * global::deltaTime);
			if (global::loaded && temp.gravityON)
			{
				temp.gravityComponent.y -= 1.7f * global::deltaTime;
			}
			
		}
	}

	void resetCounter()
	{
		start = hrc.now();
		counter = 0;
	}

	void counterTick()
	{
		type_hrc_d d = std::chrono::duration_cast<std::chrono::milliseconds>(hrc.now() - start);
		currentTick = d.count() / 1000000;
		counter += currentTick;
		start = hrc.now();
	}

	void printEntities()
	{
		vector<Entity*>::const_iterator cit;
		for (cit = entities.begin(); cit != entities.end(); ++cit)
		{
			Entity& temp = *(*cit);
			std::cout << "position: ";
			utility::printVec3(temp.position);
			std::cout << "size: ";
			utility::printVec3(temp.size);
			std::cout << "velocity: ";
			utility::printVec3(temp.velocity);
		}
	}

	long long getCount()
	{
		return counter;
	}

	void setVelocityModifier(float velMod) {
		this->velocityModifier = velMod;
	}
private:
	vector<Entity*> entities;
	long long counter;
	
	int currentTick;//miliseconds

	float velocityModifier = 17.0f;
};