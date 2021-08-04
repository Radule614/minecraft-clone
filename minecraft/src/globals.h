#ifndef GLOBALS_H
#define GLOBALS_H

#include "glm/glm.hpp"
#include "Camera.h"

#define PI 3.1415926

#define CHUNK_SIZE 16
#define CHUNK_SPAWN_RADIUS 4

namespace global {
	const unsigned int maxFPS = 210;
	unsigned int screenWidth = 1600;
	unsigned int screenHeight = 900;

	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)screenWidth / (float)screenHeight, 0.1f, 1500.0f);
	Camera camera;

	float lastX = screenWidth / 2.0;
	float lastY = screenHeight / 2.0;
	bool firstMouse = true;

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	float lastFpsDisplay = 0.0f;
	float currentFPS = 0.0f;
	float frameNumber = 0.0f;
}

#endif