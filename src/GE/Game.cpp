#include "Game.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

Game game;

void Game::loop() {
    float nextSecond = 1;
    while (!glfwWindowShouldClose(window.getGlfwWindowPtr())) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        world.get()->updateWorld();

        /* Swap front and back buffers */
        glfwSwapBuffers(window.getGlfwWindowPtr());

        /* Poll for and process events */
        glfwPollEvents();

        if (double t = glfwGetTime(); t > nextSecond) {
            std::cout << fps << std::endl;
            nextSecond = t+1;
            fps = 0;
        }
        fps++;
    }
}

void Game::init() {
    glfwSwapInterval(1);
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        terminate("ERROR:", (const char* ) glewGetErrorString(err));
    } 

    if (!GLEW_VERSION_3_0) {
        terminate("ERROR: Opengl 3.0 not supported");
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);  
}