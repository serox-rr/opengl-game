module;
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <complex>
#include <filesystem>
#include <functional>
#include <glm/glm.hpp>
#include <iostream>
#include <numbers>
#include <span>
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
        Engine::windows[0].disableVSYNC();
        Engine::settings();
        camera.setSpeed(10.0f);
        int frameAmount = 0;
        double startTime = glfwGetTime();
        Engine::Font inter("../../../game/ressources/fonts/Inter-VariableFont_slnt,wght.ttf");

        const Engine::Shader textShader({"color", "projection"}, "../../../engine/shaders/text/text.vert",
                                        "../../../engine/shaders/text/text.frag", std::nullopt, std::nullopt,
                                        std::nullopt);

        const Engine::Shader perspectiveShader(
                {"model", "transpose", "objectColor", "lightColor", "lightPos", "modelNormal", "viewPos"},
                "../../../engine/shaders/perspective/perspective.vert",
                "../../../engine/shaders/perspective/perspective.frag", std::nullopt, std::nullopt, std::nullopt);

        const Engine::Shader vectorsShader(
                {"model", "transpose", "objectColor"}, "../../../engine/shaders/vectors/vectors.vert",
                "../../../engine/shaders/vectors/vectors.frag", std::nullopt, std::nullopt, std::nullopt);

        Engine::Terrain terrain{glm::vec3(61.0 / 255.0, 33.0 / 255.0, 23.0 / 255.0), perspectiveShader};
        Engine::Vectors terrainVectors{glm::vec3(1, 1, 1), vectorsShader, terrain.getVertex()};
        Engine::Light light{glm::vec3(1.0, 1.0, 1.0), glm::vec3(50, 10, sin(glfwGetTime()) * 20 + 50), vectorsShader};
        Engine::Vectors lightVectors{glm::vec3(1, 1, 1), vectorsShader, light.getVertex()};
        Engine::Text coordsText("142", glm::vec3(100, 0, 0), glm::vec3(0.5, 0.8f, 0.2f), 0.5f, inter, textShader);
        Engine::Text fpsText("fps: 0", glm::vec3(0, 0, 0), glm::vec3(0.5, 0.8f, 0.2f), 0.5f, inter, textShader);
        std::reference_wrapper<const Engine::Shader> perspectiveShaders[] = {std::reference_wrapper(perspectiveShader),
                                                                             std::reference_wrapper(vectorsShader)};
        Engine::PerspectiveRenderer perspectiveRenderer(camera, {terrain, light, lightVectors, /*terrainVectors*/},
                                                        perspectiveShaders);
        while (!glfwWindowShouldClose(Engine::windows[0])) {
            // input
            // -----
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            Game::processInput(Engine::windows[0]);
            glfwSetCursorPosCallback(Engine::windows[0], Game::mouse_callback);
            glfwSetScrollCallback(Engine::windows[0], Game::scroll_callback);
            double teta = std::fmod(glfwGetTime(), 100) / 50 * std::numbers::pi * 10;
            double r = 10000;
            double zLight = r * cos(teta);
            double yLight = r * sin(teta);
            light.setColor(glm::vec3(1, 1, 1));
            light.setPosition(glm::vec3(5000, 5000, 5000));
            coordsText.render();
            fpsText.render();
            perspectiveRenderer.render();
            double currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;
            auto pos = camera.getPosition();
            coordsText.setContent("X: " + std::to_string(pos.x) + " Y: " + std::to_string(pos.y) +
                                  " Z: " + std::to_string(pos.z));
            glfwSwapBuffers(Engine::windows[0]);
            glfwPollEvents();
            if (glfwGetTime() - startTime > 1.0f) {
                fpsText.setContent("fps: " + std::to_string(frameAmount));
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
    camera.setSpeed(500.0f * deltaTime);
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
