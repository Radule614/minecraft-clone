#include "src/setup.h"

using namespace std;
using namespace global;
using namespace util;

int main()
{
    GLFWwindow* window = util::setup();

    Shader UI_shader("res\\shaders\\UI_vertex.glsl", "res\\shaders\\UI_fragment.glsl");
    Shader objectShader("res\\shaders\\vertex.glsl", "res\\shaders\\fragment.glsl");

    TextureLoader::load("res\\textures\\atlas.png", 0);
    objectShader.setUniformInt("atlas", 0);

    TextureLoader::load("res\\textures\\crosshair.png", 1);
    UI_shader.setUniformInt("crosshair", 1);

    objectShader.setUniformFloat("texture_size", 48);
    objectShader.setUniformFloat("atlas_size", 768);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    World world;

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        //if (deltaTime < 1.0 / maxFPS) continue;
        lastFrame = currentFrame;
        fpsCounter();
        //glClearColor(0.25f, 0.5f, 1.0f, 1.0f);
        glClearColor(0.3961f, 0.7608f, 96.08f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        objectShader.bind();
        objectShader.resetModelMatrix();
        objectShader.setUniformMatrix("projection", projection);
        objectShader.setUniformMatrix("view", camera.getView());
        
        world.draw();

        processInput(window);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

	return 0;
}