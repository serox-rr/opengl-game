module;
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <complex>
#include <filesystem>
#include <functional>
#include <glm/glm.hpp>
#include <iostream>
#include <span>
module game;

import engine;

int main() {
    try {
        Engine::init();
        Engine::windows.emplace_back(1920, 1080);
        Engine::windows[0].setInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        // Engine::windows[0].disableVSYNC();
        Engine::settings();
        int frameAmount = 0;
        double startTime = glfwGetTime();
        Engine::Font inter("../../../game/resources/fonts/Inter-VariableFont_slnt,wght.ttf");

        Engine::Shader textShader({"color", "projection"}, "../../../engine/shaders/text/text.vert",
                                  "../../../engine/shaders/text/text.frag", std::nullopt, std::nullopt, std::nullopt);

        Engine::Shader perspectiveShader(
                {"model", "transpose", "objectColor", "lightColor", "lightPos", "modelNormal", "viewPos"},
                "../../../engine/shaders/perspective/perspective.vert",
                "../../../engine/shaders/perspective/perspective.frag", std::nullopt, std::nullopt, std::nullopt);

        Engine::Shader simpleShader({"model", "transpose", "objectColor"}, "../../../engine/shaders/simple/simple.vert",
                                    "../../../engine/shaders/simple/simple.frag", std::nullopt, std::nullopt,
                                    std::nullopt);

        Engine::Shader terrainShader({"transpose", "model", "heightMap", "viewPos", "material.ambient",
                                      "material.diffuse", "material.specular", "material.shininess", "light.direction",
                                      "light.ambient", "light.diffuse", "light.specular"},
                                     "../../../engine/shaders/terrain/terrain.vert",
                                     "../../../engine/shaders/terrain/terrain.frag", std::nullopt,
                                     "../../../engine/shaders/terrain/terrain.tesc",
                                     "../../../engine/shaders/terrain/terrain.tese");

        Engine::Shader modelShader({"transpose", "model", "viewPos"}, "../../../engine/shaders/model/model.vert",
                                   "../../../engine/shaders/model/model.frag", std::nullopt, std::nullopt,
                                   std::nullopt);


        Engine::Terrain terrain{glm::vec3(61.0 / 255.0, 33.0 / 255.0, 23.0 / 255.0), terrainShader};
        Engine::Text coordsText("142", glm::vec3(100, 0, 0), glm::vec3(0.5, 0.8f, 0.2f), 0.5f, inter, textShader);
        Engine::Text fpsText("fps: 0", glm::vec3(0, 0, 0), glm::vec3(0.5, 0.8f, 0.2f), 0.5f, inter, textShader);
        Engine::points =
                std::make_unique<Engine::Points>(Engine::Points(glm::vec3(1.0, 0.0, 0.0), simpleShader, {0, 60, 0}));
        std::initializer_list<std::reference_wrapper<const Engine::Renderable>> collidables = {
                std::reference_wrapper(terrain)};
        Engine::Player player(glm::vec3(0.0, 60.0f, 0.0), -90.0, 0.0, 1.9, collidables, 70);
        std::reference_wrapper<Engine::Shader> perspectiveShaders[] = {std::reference_wrapper(perspectiveShader),
                                                                             std::reference_wrapper(simpleShader),
                                                                             std::reference_wrapper(terrainShader)};
        Engine::PerspectiveRenderer perspectiveRenderer(dynamic_cast<Engine::Camera &>(player.getActiveCamera()), {terrain, *Engine::points.get()}, perspectiveShaders);


        Engine::Model model("../../../game/resources/models/backpack/backpack.obj", glm::vec3(0, 60, 0), modelShader);
        std::reference_wrapper<Engine::Shader> modelShaders[] = {std::reference_wrapper(modelShader)};
        Engine::ModelRenderer modelRenderer(player.getActiveCamera(), {model}, modelShaders);
        while (!glfwWindowShouldClose(Engine::windows[0])) {
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            Engine::updateTime();
            coordsText.render();
            fpsText.render();
            player.processInput(Engine::windows[0]);
            player.update();
            perspectiveRenderer.render();
            modelRenderer.render();
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
