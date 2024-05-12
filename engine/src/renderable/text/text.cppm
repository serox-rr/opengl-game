module;
#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <string_view>
export module engine:renderable.text;
import :renderable;
import :font;

export namespace Engine {
    class Text final : public Renderable {
    public:
        Text(std::string_view content_, const glm::vec3 &position_, const glm::vec3 &color_, float scale_, Font &font_,
             Shader &shader_);

        void render() const override;

        ~Text() override;

        void setContent(std::string_view content_) ;

    private:
        std::string content;
        float scale;
        Font &font;
    };
} // namespace Engine
