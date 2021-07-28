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

#include "src/quad.h"

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

    Quad s1(Quad::FRONT);
    Quad s2(Quad::BACK);
    Quad s3(Quad::LEFT);
    Quad s4(Quad::RIGHT);
    Quad s5(Quad::TOP);
    Quad s6(Quad::BOTTOM);

    Shader objectShader("res\\shaders\\vertex.glsl", "res\\shaders\\fragment.glsl");

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        if (deltaTime < 1.0 / maxFPS) continue;
        lastFrame = currentFrame;
        fpsCounter();
        glClearColor(0.25f, 0.5f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        objectShader.bind();
        objectShader.resetModelMatrix();
        objectShader.setUniformMatrix("projection", projection);
        objectShader.setUniformMatrix("view", camera.getView());
        objectShader.updateModelMatrix(Shader::translate, glm::vec3(0.0f));
        objectShader.updateModelMatrix(Shader::scale, glm::vec3(0.5f));
        s1.draw();
        s2.draw();
        s3.draw();
        s4.draw();
        s5.draw();
        s6.draw();

        processInput(window);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

	return 0;
}