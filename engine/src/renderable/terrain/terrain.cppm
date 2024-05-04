module;
#include <glm/glm.hpp>
#include <vector>

export module engine:renderable.terrain;
import :shader;
import :renderable;

export namespace Engine {
    class Terrain final: public Renderable {
    public:
        explicit Terrain(const glm::vec3 &color, const Shader &shader_);
        void render() override;
        ~Terrain() override;


    private:
        unsigned width, height;
        glm::vec3 position;
    };
}
