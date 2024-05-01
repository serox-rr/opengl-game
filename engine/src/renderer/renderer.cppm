module;
#include <functional>
#include <span>
#include <vector>
export module engine:renderer;
import :shader;
import :renderable;

export namespace Engine {
    class Renderer {
    public:
        Renderer(const std::span<std::reference_wrapper<Shader>>& shaders_, const std::vector<std::reference_wrapper<Renderable>>& renderables_): shaders(shaders_), renderables(renderables_) {};
        virtual void render() = 0;
        virtual ~Renderer() = default;
    protected:
        const std::span<std::reference_wrapper<Shader>>& shaders;
        std::vector<std::reference_wrapper<Renderable>> renderables;
    };
} // namespace Engine
