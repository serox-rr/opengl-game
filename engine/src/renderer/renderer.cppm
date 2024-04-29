module;
#include <vector>
#include <functional>
export module engine:renderer;
import :shader;
import :renderable;

export namespace Engine {
    class Renderer {
    public:
        Renderer(const Shader& shader_, const std::vector<std::reference_wrapper<Renderable>>& renderables_): shader(shader_), renderables(renderables_) {};
        virtual void render() = 0;
        virtual ~Renderer() = default;
    protected:
        const Shader& shader;
        std::vector<std::reference_wrapper<Renderable>> renderables;
    };
} // namespace Engine
