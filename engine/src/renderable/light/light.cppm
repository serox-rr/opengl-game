module;
#include <glm/glm.hpp>

export module engine:renderable.light;
import :renderable;

export namespace Engine {
    class Light final : public Renderable {
    public:
        explicit Light();

        void render() override;

        ~Light() override;
    private:
        glm::vec3 position;
    };
}
