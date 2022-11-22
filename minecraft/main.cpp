#include "src/setup.hpp"

using namespace std;
using namespace global;

int main()
{
    GLFWwindow* window = setup::setup();

    TextureLoader::load("res\\textures\\atlas.png", 0);
    TextureLoader::load("res\\textures\\crosshair.png", 1);
    Shader UI_shader("res\\shaders\\UI_vertex.glsl", "res\\shaders\\UI_fragment.glsl");
    UI_shader.setUniformInt("crosshair", 1);

    Shader objectShader("res\\shaders\\vertex.glsl", "res\\shaders\\fragment.glsl");
    objectShader.setUniformInt("atlas", 0);

    objectShader.setUniformFloat("texture_size", 48);
    objectShader.setUniformFloat("atlas_size", 768);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    World world;
    Player player(world, camera.position, glm::vec3(1, 2, 1), false);

    Physics engine;
    global::camera.type = Camera::FREELOOK;
    engine.setVelocityModifier(120);
    engine.pushEntity(&player);

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        if (deltaTime < 1.0 / maxFPS) continue;
        lastFrame = currentFrame;
        setup::fpsCounter();
        engine.counterTick();
        engine.updateGravity();
        glClearColor(0.3961f, 0.7608f, 96.08f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        player.move();

        if (pressedKeys[GLFW_MOUSE_BUTTON_LEFT])
        {
            player.castRay(engine.getCount());
        }

        objectShader.bind();
        objectShader.resetModelMatrix();
        objectShader.setUniformMatrix("projection", projection);
        objectShader.setUniformMatrix("view", camera.getView());
        world.draw();

        UI_shader.bind();
        UI_shader.setUniformMatrix("projection", projection);
        UI::drawCrosshair();

        setup::processInput(window);
        glfwSwapBuffers(window);
        glfwPollEvents();

        if (!global::loaded) global::loaded = true;
        global::lastFrameTime = glfwGetTime() - currentFrame;
    }

    glfwTerminate();

	return 0;
}