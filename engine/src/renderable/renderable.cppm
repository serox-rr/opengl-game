module;
#include <glm/glm.hpp>
#include <vector>
export module engine:renderable;
import :shader;

export namespace Engine {
    class Renderable {
    public:
        Renderable(const unsigned vao, const unsigned vbo, const glm::vec3 &color_, const glm::vec3 position_, const std::vector<float> &vertex_,
                   const Shader &shader_) : vao(vao), vbo(vbo), color(color_), position(position_), shader(shader_), vertices(vertex_){};
        virtual void render() = 0;
        virtual ~Renderable() = default;
        [[nodiscard]] glm::vec3 getColor() const { return color; }

        void setColor(const glm::vec3 &color_) { color = color_; }


        [[nodiscard]] glm::vec3 getPosition() const { return position; }

        void setPosition(const glm::vec3 &position_) { position = position_; }


        [[nodiscard]] const Shader &getShader() const { return shader; }

         [[nodiscard]] std::vector<float> getVertex() const { return vertices; }

    protected:
        unsigned vao, vbo;
        glm::vec3 color, position;
        const Shader &shader;
        std::vector<float> vertices;
    };
} // namespace Engine
