module;
#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <string>
export module engine:renderable.text;
import :renderable;
import :font;

export namespace Engine {
    class Text final : public Renderable {
    public:
        Text(const std::string &content_, const glm::vec2 &position_, const glm::vec3 &color_,
             float scale_, const Font &font_);

        void render() override;

        ~Text() override;

    private:
        std::string content;
        glm::vec2 position;
        glm::vec3 color;
        float scale;
        Font font;
        const Shader shader;
    };
} // namespace Engine
