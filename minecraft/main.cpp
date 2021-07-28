#define GLEW_STATIC

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "src/shader.h"

#include "src/globals.h"

#include "src/tex.h"

#include "src/cube.h"

using namespace std;
using namespace global;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    screenWidth = width;
    screenHeight = height;
    projection = glm::perspective(glm::radians(45.0f), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE))
    {
        glfwSetWindowShouldClose(window, true);
    }
    camera.speed = 10.0f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera.position += camera.speed * camera.front;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera.position -= camera.speed * camera.front;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera.position += camera.speed * glm::cross(camera.front, camera.up);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera.position -= camera.speed * glm::cross(camera.front, camera.up);
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
        cout << "FPS: " << currentFPS << endl;
    }
}

int main()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(screenWidth, screenHeight, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "GLEW NOT OK" << std::endl;
        exit(-2);
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glViewport(0, 0, screenWidth, screenHeight);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    Cube kocka;

    Shader objectShader("res\\shaders\\vertex.glsl", "res\\shaders\\fragment.glsl");

    int start = glfwGetTime();
    int delta;

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        //if (deltaTime < 1.0 / maxFPS) continue;
        lastFrame = currentFrame;
        fpsCounter();
        glClearColor(0.25f, 0.5f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        objectShader.bind();
        objectShader.resetModelMatrix();
        objectShader.setUniformMatrix("projection", projection);
        objectShader.setUniformMatrix("view", camera.getView());
        double color = 0;
        for (int i = 0; i < 100; i++)
        {
            for (int j = 0; j < 100; j++)
            {
                objectShader.setUniformVec3("color", glm::vec3(0.01+color, 0.5+color/2, 0.1+color/3));
                objectShader.resetModelMatrix();
                objectShader.updateModelMatrix(Shader::translate, glm::vec3(2 * j, 0.0f, -2 * i));
                kocka.draw();
                
                color += abs(sin(glfwGetTime()*cos(glfwGetTime())));
                if (color >= 1.0) color = 0;
            }
        }
        
        processInput(window);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

	return 0;
}