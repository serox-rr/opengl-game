module;
#include <glm/glm.hpp>

export module engine:renderable.light;
import :renderable;

export namespace Engine {
    class Light final : public Renderable {
    public:
        explicit Light(const glm::vec3 &color, const glm::vec3 &position_, const Shader &shader_);

        void render() override;

        ~Light() override;
    };
}
