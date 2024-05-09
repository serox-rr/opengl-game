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

int main() {
    try {
        Engine::init();
        Engine::windows.emplace_back(1920, 1080);
        Engine::windows[0].setInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        // Engine::windows[0].disableVSYNC();)
        Engine::Camera camera(glm::vec3(0.0f, 70.0f, 0.0f));
        Engine::settings();
        camera.setSpeed(10.0f);
        int frameAmount = 0;
        double startTime = glfwGetTime();
        Engine::Font inter("../../../game/resources/fonts/Inter-VariableFont_slnt,wght.ttf");

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

        const Engine::Shader terrainShader(
                {"transpose", "model", "heightMap","viewPos", "material.ambient", "material.diffuse", "material.specular",
                 "material.shininess", "light.direction", "light.ambient", "light.diffuse", "light.specular"},
                "../../../engine/shaders/terrain/terrain.vert", "../../../engine/shaders/terrain/terrain.frag",
                std::nullopt, "../../../engine/shaders/terrain/terrain.tesc",
                "../../../engine/shaders/terrain/terrain.tese");

        Engine::Terrain terrain{glm::vec3(61.0 / 255.0, 33.0 / 255.0, 23.0 / 255.0), terrainShader};
        Engine::Light light{glm::vec3(1.0, 1.0, 1.0), glm::vec3(50, 10, sin(glfwGetTime()) * 20 + 50), vectorsShader};
        Engine::Text coordsText("142", glm::vec3(100, 0, 0), glm::vec3(0.5, 0.8f, 0.2f), 0.5f, inter, textShader);
        Engine::Text fpsText("fps: 0", glm::vec3(0, 0, 0), glm::vec3(0.5, 0.8f, 0.2f), 0.5f, inter, textShader);
        std::initializer_list<std::reference_wrapper<const Engine::Renderable>> collidables = {std::reference_wrapper(terrain)};
        Engine::Player player(glm::vec3(0.0, 70.0f, 0.0), -90.0, 0.0, 10, camera, collidables);
        std::reference_wrapper<const Engine::Shader> perspectiveShaders[] = {std::reference_wrapper(perspectiveShader),
                                                                             std::reference_wrapper(vectorsShader),
                                                                             std::reference_wrapper(terrainShader)};
        Engine::PerspectiveRenderer perspectiveRenderer(camera, {terrain, light}, perspectiveShaders);
        while (!glfwWindowShouldClose(Engine::windows[0])) {
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            Engine::updateTime();
            double teta = std::fmod(glfwGetTime(), 100) / 50 * std::numbers::pi * 10;
            double r = 500;
            double zLight = r * cos(teta);
            double yLight = r * abs(sin(teta));
            light.setColor(glm::vec3(1, 1, 1));
            light.setPosition(glm::vec3(0, yLight, zLight));
            coordsText.render();
            fpsText.render();
            perspectiveRenderer.render();
            player.processInput(Engine::windows[0]);
            auto pos = player.getPosition();
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
