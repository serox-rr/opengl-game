module;
#include <filesystem>
#include <vector>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/fwd.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
module game;

import engine;
import engine.renderable.terrain;
import engine.renderable.light;

float deltaTime = 0.0f; // Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame
bool firstMouse = true;
Engine::Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

int main() {
    try {
        Engine::init();
    const Engine::Window window(1920, 1080);
    window.setInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    Engine::settings();
    Engine::initFreeType();
    Engine::shaders.emplace_back(Engine::Shader(R"(../../../engine/shaders/coords/coords.vert)",
                                      R"(../../../engine/shaders/coords/coords.frag)",
                                      std::vector({"transpose", "time", "model"})));
    camera.setSpeed(10.0f);
    Engine::shaders[0].use();
    int frameAmount = 0;
    float startTime = glfwGetTime();
    Engine::Text terrain{};
    Engine::Light light{};
    while (!glfwWindowShouldClose(window)) {
        // input
        // -----
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        Game::processInput(window);
        glfwSetCursorPosCallback(window, Game::mouse_callback);
        glfwSetScrollCallback(window, Game::scroll_callback);
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(10000.0f,10000.0f,10000.0f));
        Engine::shaders[0].setMat4("model", model);
        glm::mat4 projection = glm::perspective(glm::radians(camera.getFov()),
                                                static_cast<float>(window.getWidth() / window.getHeight()), 0.1f,
                                                100000000.0f);
        glm::mat4 transpose = projection * *camera.getView() * model;
        Engine::shaders[0].setMat4("transpose", transpose);
        Engine::shaders[0].setFloat("time", currentFrame);
        terrain.render();
        light.render();
        glfwSwapBuffers(window);
        glfwPollEvents();
        if (glfwGetTime() - startTime > 1.0f) {
            std::cout << frameAmount << " fps" << std::endl;
            startTime = glfwGetTime();
            frameAmount = 0;
        }
        frameAmount++;
    }
    glfwTerminate();
    } catch (std::exception const& e) {
        std::cout << e.what() << std::endl;
        return -1;
    }
    return 0;
}

void Game::processInput(GLFWwindow* window) {
    camera.setSpeed(100000.0f * deltaTime);
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
void Game::mouse_callback(GLFWwindow* window, const double xpos, const double ypos) {
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
    camera.setLookingDirection(camera.getYaw() + xoffset,
                               camera.getPitch() + yoffset);
}

void Game::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    camera.setFov(camera.getFov() - static_cast<float>(yoffset));
}
