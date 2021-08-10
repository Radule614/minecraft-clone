#ifndef GLOBALS_H
#define GLOBALS_H

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "camera.h"

#define PI 3.1415926

#define CHUNK_SIZE_X 16
#define CHUNK_SIZE_Y 128
#define CHUNK_SIZE_Z 16
#define CHUNK_SPAWN_RADIUS 4

namespace global {
	const unsigned int maxFPS = 210;
	unsigned int screenWidth = 1600;
	unsigned int screenHeight = 900;

	glm::mat4 projection = glm::perspective(glm::radians(55.0f), (float)screenWidth / (float)screenHeight, 0.1f, 1500.0f);
	Camera camera(glm::vec3(5*16.0f, 0.0f, 5 * (-16.0f)));

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