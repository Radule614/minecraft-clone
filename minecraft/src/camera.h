#ifndef CAMERA_H
#define CAMERA_H

#include "glm/glm.hpp"

class Camera{
private:
	float pitch;
	float yaw;
public:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	float sensitivity;
	float speed;
	Camera() : pitch(0.0f), yaw(-90.0f), sensitivity(0.1f), speed(0)
	{
		position = glm::vec3(0.0f, 0.0f, 10.0f);
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

	glm::mat4 getView() const
	{
		return glm::lookAt(position, front + position, up);
	}
};

#endif