#pragma once

#include "GLEW/glew.h"
#include "GLFW/glfw3.h"

#include <map>

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera{
private:
	float pitch;
	float yaw;
public:
	enum Type {FREELOOK = 0, FPS};
	
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	float sensitivity;
	float speed;
	Type type;

	glm::vec3 direction;
	
	glm::vec3 velocity;
	glm::vec3 oldPosition;

	

	Camera(Type t, glm::vec3 pos = glm::vec3(0.0f)) : type(t), pitch(0.0f), yaw(-90.0f), sensitivity(0.1f), speed(0)
	{
		position = pos;
		front = glm::vec3(0.0f, 0.0f, -1.0f);
		up = glm::vec3(0.0, 1.0f, 0.0f);
	}

	void calculateDirection(float& xoffset, float& yoffset)
	{
		float sensitivity = 0.1f;
		xoffset *= sensitivity;
		yoffset *= sensitivity;
		yaw += xoffset;
		pitch += yoffset;
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;
		glm::vec3 direction;
		direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		direction.y = sin(glm::radians(pitch));
		direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		front = glm::normalize(direction);
	}

	glm::vec3 calculateMoveDirection(std::map<unsigned int, bool>& pressedKeys)
	{
		glm::vec3 dirVector_front = glm::vec3(0);
		glm::vec3 dirVector_side = glm::vec3(0);
		if (pressedKeys[GLFW_KEY_W])
		{
			dirVector_front = glm::normalize(front);
		}
		if (pressedKeys[GLFW_KEY_S])
		{
			dirVector_front = -glm::normalize(front);
		}
		if (pressedKeys[GLFW_KEY_D])
		{
			dirVector_side = glm::normalize(glm::cross(front, up));
		}
		if (pressedKeys[GLFW_KEY_A])
		{
			dirVector_side = -glm::normalize(glm::cross(front, up));
		}
		
		if (dirVector_front != glm::vec3(0) || dirVector_side != glm::vec3(0))
		{	
			if (type == FPS)
			{
				glm::vec3 temp = dirVector_front;
				temp.y = 0;
				direction = glm::normalize(temp + dirVector_side);
			}
			else
			{
				direction = glm::normalize(dirVector_front + dirVector_side);
			}
		}
		return direction;
	}

	void setVelocity(glm::vec3 vel)
	{
		this->velocity = speed * vel;
	}

	void move()
	{
		oldPosition = position;
		position += velocity;
	}

	glm::mat4 getView() const
	{
		return glm::lookAt(position, front + position, up);
	}
};