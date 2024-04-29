module;
#include <glm/glm.hpp>

export module engine:renderable.terrain;
import :shader;
import :renderable;

export namespace Engine {
    class Terrain final: public Renderable {
    public:
        explicit Terrain();
        void render() override;
        ~Terrain() override;
    private:
        unsigned width, height;
        glm::vec3 position{};
    };
}
