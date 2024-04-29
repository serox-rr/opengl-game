module;
#include <algorithm>
#include <functional>
#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <vector>
module engine;

namespace Engine {

    PerspectiveRenderer::PerspectiveRenderer(Camera &camera_,
                                             const std::vector<std::reference_wrapper<Renderable>> &renderables_,
                                             const Shader &shader_) :
        Renderer(shader_, renderables_), camera(camera_) {}

    void PerspectiveRenderer::render() {
        glm::mat4 model = glm::mat4(1.0f);
        const Window window = windows[0];
        const glm::mat4 projection =
                glm::perspective(glm::radians(camera.getFov()), static_cast<float>(window.getWidth()/window.getHeight()), 0.1f, 100000000.0f);
        glm::mat4 transpose = projection * camera.getView();
        shader.use();
        shader.setMat4("transpose", transpose);
        shader.setMat4("model", model);
        std::ranges::for_each(renderables.begin(), renderables.end(),
                              [](Renderable &renderable) { renderable.render(); });
    }

} // namespace Engine
