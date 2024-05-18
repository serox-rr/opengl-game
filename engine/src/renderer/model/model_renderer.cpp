module;
#include <algorithm>
#include <functional>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <iostream>
#include <span>
#include <vector>
module engine;

namespace Engine {

    ModelRenderer::ModelRenderer(Player &player_, const std::vector<std::reference_wrapper<Model>> &models_,
                                 const std::span<std::reference_wrapper<Shader>> &shaders_) :
        Renderer(shaders_, models_), player(player_) {}

    void ModelRenderer::render() const {
        const Window window = windows[0];
        Camera &camera = player.getActiveCamera();
        const glm::mat4 projection =
                glm::perspective(glm::radians(camera.getFov()),
                                 static_cast<float>(window.getWidth()) / static_cast<float>(window.getHeight()), 0.1f, 100000000.0f);
        const glm::mat4 transpose = projection * camera.getView();
        std::ranges::for_each(shaders.begin(), shaders.end(), [&transpose]( Shader &shader) {
            shader.use();
            shader.setMat4("transpose", transpose);
            shader.addUniforms({"light.direction", "light.ambient", "light.diffuse", "light.specular"});
            shader.setVec3("light.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
            shader.setVec3("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
            shader.setVec3("light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
            shader.setVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        });
        std::ranges::for_each(renderables.begin(), renderables.end(), [](const Model &model) {
            const auto shader = model.getShader();
            shader.use();
            shader.setMat4("model", glm::translate(glm::mat4(1.0f), model.getPosition()));
            model.render();
        });
    }

} // namespace Engine
