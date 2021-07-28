#ifndef GLOBALS_H
#define GLOBALS_H

#include "glm/glm.hpp"
#include "Camera.h"

namespace global {
	const unsigned int maxFPS = 200;
	unsigned int screenWidth = 1270;
	unsigned int screenHeight = 720;

	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)screenWidth / (float)screenHeight, 0.1f, 500.0f);
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