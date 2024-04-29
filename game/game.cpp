module;
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <filesystem>
#include <glm/glm.hpp>
#include <iostream>
#include <map>
module game;

import engine;

float deltaTime = 0.0f; // Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame
bool firstMouse = true;
Engine::Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

int main() {
    try {
        Engine::init();
        Engine::windows.emplace_back(1920, 1080);
        Engine::windows[0].setInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        Engine::settings();
        Engine::Shader shader(R"(../../../engine/shaders/perspective/perspective.vert)",
                              R"(../../../engine/shaders/perspective/perspective.frag)",
                              {"transpose", "time", "model"});
        camera.setSpeed(10.0f);
        int frameAmount = 0;
        float startTime = glfwGetTime();
        Engine::Terrain terrain{};
        Engine::Light light{};
        Engine::Font inter("../../../game/ressources/fonts/Inter-VariableFont_slnt,wght.ttf");
        Engine::Text text("Hello world !", glm::vec2(0, 0), glm::vec3(1.0, 1.0, 1.0), 1.0f, inter);
        Engine::Shader perspectiveShader("../../../engine/shaders/perspective/perspective.vert",
                                         "../../../engine/shaders/perspective/perspective.frag",
                                         {"model", "transpose"});
        Engine::PerspectiveRenderer perspectiveRenderer(camera, {terrain, light}, perspectiveShader);
        while (!glfwWindowShouldClose(Engine::windows[0])) {
            // input
            // -----
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            Game::processInput(Engine::windows[0]);
            glfwSetCursorPosCallback(Engine::windows[0], Game::mouse_callback);
            glfwSetScrollCallback(Engine::windows[0], Game::scroll_callback);
            text.render();
            perspectiveRenderer.render();
            float currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;
            glfwSwapBuffers(Engine::windows[0]);
            glfwPollEvents();
            if (glfwGetTime() - startTime > 1.0f) {
                std::cout << frameAmount << " fps" << std::endl;
                startTime = glfwGetTime();
                frameAmount = 0;
            }
            frameAmount++;
        }
        glfwTerminate();
    }
    catch (std::exception const &e) {
        std::cout << e.what() << std::endl;
        return -1;
    }
    return 0;
}

void Game::processInput(GLFWwindow *window) {
    camera.setSpeed(10.0f * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.moveForward();
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.moveBackward();
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.moveLeft();
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.moveRight();
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.moveUp();
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        camera.moveDown();
}

float lastX = 400, lastY = 300;

void Game::mouse_callback(GLFWwindow *window, const double xpos, const double ypos) {
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates range from bottom to top
    lastX = xpos;
    lastY = ypos;
    if (firstMouse) // initially set to true
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    xoffset *= camera.getSensitivity();
    yoffset *= camera.getSensitivity();
    camera.setLookingDirection(camera.getYaw() + xoffset, camera.getPitch() + yoffset);
}

void Game::scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    camera.setFov(camera.getFov() - static_cast<float>(yoffset));
}
