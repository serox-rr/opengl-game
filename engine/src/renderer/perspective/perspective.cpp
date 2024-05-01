module;
#include <algorithm>
#include <functional>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <span>
#include <vector>
module engine;

namespace Engine {

    PerspectiveRenderer::PerspectiveRenderer(Camera &camera_,
                                             const std::vector<std::reference_wrapper<Renderable>> &renderables_,
                                             const std::span<std::reference_wrapper<Shader>> &shaders_) :
        Renderer(shaders_, renderables_), camera(camera_) {}

    void PerspectiveRenderer::render() {
        glm::mat4 model(1.0f);
        const Window window = windows[0];
        const glm::mat4 projection =
                glm::perspective(glm::radians(camera.getFov()),
                                 static_cast<float>(window.getWidth() / window.getHeight()), 0.1f, 100000000.0f);
        const glm::mat4 transpose = projection * camera.getView();
        const Renderable &renderable2 = renderables[1];
        std::ranges::for_each(shaders.begin(), shaders.end(), [transpose, renderable2](const Shader &shader) {
            shader.use();
            shader.setMat4("transpose", transpose);
            shader.setVec3("lightColor", renderable2.getColor());
            shader.setVec3("lightPos", glm::vec3(10,15,10));
        });
        std::ranges::for_each(renderables.begin(), renderables.end(), [&](Renderable &renderable) {
            model = glm::translate(model, renderable.getPosition());
            renderable.getShader().setMat4("model", model);
            renderable.render();
        });
    }

} // namespace Engine
