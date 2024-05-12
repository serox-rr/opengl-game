module;
#include <glm/glm.hpp>
#include <vector>

export module engine:renderable.terrain;
import :shader;
import :renderable;

export namespace Engine {
    class Terrain final: public Renderable {
    public:
        explicit Terrain(const glm::vec3 &color, Shader &shader_);
        void render() const override;
        ~Terrain() override;
        [[nodiscard]] const std::vector<float> &getHeightMap() const;
        [[nodiscard]] const int &getWidth() const;
        [[nodiscard]] const int &getHeight() const;
        [[nodiscard]] const int &getRez() const;

    private:
        int  width, height, rez;
        glm::vec3 position;
        std::vector<float> heightMap;
    };
}
