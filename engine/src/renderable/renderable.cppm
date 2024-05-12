module;
#include <glm/glm.hpp>
#include <string>
#include <vector>
export module engine:renderable;
import :shader;
export namespace Engine {
    struct Vertex {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 TexCoords;
    };

    struct ModelTexture {
        unsigned id{0};
        std::string type{};
        std::string path{};
    };

    class Renderable {
    public:
        Renderable(const unsigned vao, const unsigned vbo, const glm::vec3 &color_, const glm::vec3 position_,
                   const std::vector<float> &vertices_, Shader &shader_) :
            vao(vao), vbo(vbo), color(color_), position(position_), shader(shader_), vertices(vertices_){};
        virtual void render() const = 0;
        virtual ~Renderable() = default;
        [[nodiscard]] glm::vec3 getColor() const { return color; }

        void setColor(const glm::vec3 &color_) { color = color_; }


        [[nodiscard]] glm::vec3 getPosition() const { return position; }

        void setPosition(const glm::vec3 &position_) { position = position_; }


        [[nodiscard]] const Shader &getShader() const { return shader; }

        [[nodiscard]] std::vector<float> getVertices() const { return vertices; }

    protected:
        unsigned vao, vbo;
        glm::vec3 color, position;
        Shader &shader;
        std::vector<float> vertices;
    };

} // namespace Engine
