#pragma once

#define GLEW_STATIC

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "src/utility/utility.h"

#include <iostream>
#include <map>

#include "src/utility/texture_loader.h"
#include "src/shader.h"
#include "src/globals.h"
#include "UI/UI.h"

#include "src/world/world.h"
#include "entity/player.h"

namespace setup {
    void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
        screenWidth = width;
        screenHeight = height;
        projection = glm::perspective(glm::radians(45.0f), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
    }

    void processInput(GLFWwindow* window)
    {
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        {
            global::pressedKeys[GLFW_KEY_SPACE] = true;
        }
        else
        {
            global::pressedKeys[GLFW_KEY_SPACE] = false;
        }
        if (glfwGetKey(window, GLFW_KEY_ESCAPE))
        {
            glfwSetWindowShouldClose(window, true);
        }
        camera.speed = 50.0f * deltaTime;
        
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            global::pressedKeys[GLFW_KEY_W] = true;
        }
        else
        {
            global::pressedKeys[GLFW_KEY_W] = false;
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            global::pressedKeys[GLFW_KEY_S] = true;
        }
        else
        {
            global::pressedKeys[GLFW_KEY_S] = false;
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            global::pressedKeys[GLFW_KEY_D] = true;
        }
        else
        {
            global::pressedKeys[GLFW_KEY_D] = false;
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            global::pressedKeys[GLFW_KEY_A] = true;
        }
        else
        {
            global::pressedKeys[GLFW_KEY_A] = false;
        }
    }

    void mouse_callback(GLFWwindow* window, double xpos, double ypos)
    {
        if (firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }
        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos;
        lastX = xpos;
        lastY = ypos;
        camera.calculateDirection(xoffset, yoffset);
    }

    void fpsCounter()
    {
        if (glfwGetTime() - lastFpsDisplay < 1)
        {
            frameNumber++;
        }
        else
        {
            currentFPS = frameNumber;
            lastFpsDisplay = glfwGetTime();
            frameNumber = 0;
        }
    }

    GLFWwindow* setup()
    {
        GLFWwindow* window;
        if (!glfwInit()) exit(-2);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        window = glfwCreateWindow(screenWidth, screenHeight, "Game", NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            exit(-2);
        }
        glfwMakeContextCurrent(window);
        if (glewInit() != GLEW_OK)
        {
            std::cout << "GLEW NOT OK" << std::endl;
            exit(-2);
        }

        //settings
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        glfwSetCursorPosCallback(window, mouse_callback);
        glViewport(0, 0, screenWidth, screenHeight);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glEnable(GL_DEPTH_TEST);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);

        Cube::initiateData();

        UI::setCrosshair();

        return window;
    }
};

