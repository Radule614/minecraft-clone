#pragma once

#include <map>

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define PI 3.1415926

#define CHUNK_SIZE_X 16
#define CHUNK_SIZE_Y 144
#define CHUNK_SIZE_Z 16
#define CHUNK_SPAWN_RADIUS 4
#define CHUNK_NUMBER 16

#include "camera.hpp"

namespace global {
	std::map<unsigned int, bool> pressedKeys;

	const unsigned int maxFPS = 100;
	unsigned int screenWidth = 1600;
	unsigned int screenHeight = 900;

	glm::mat4 projection = glm::perspective(glm::radians(55.0f), (float)screenWidth / (float)screenHeight, 0.1f, 1500.0f);
	Camera camera(Camera::FREELOOK, glm::vec3(16.0f, -32.0f, -16.0f));
	//glm::vec3(5*16.0f, -16.0f, 5 * (-16.0f))
	float lastX = screenWidth / 2.0;
	float lastY = screenHeight / 2.0;
	bool firstMouse = true;

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	float lastFpsDisplay = 0.0f;
	float currentFPS = 0.0f;
	float frameNumber = 0.0f;

}