module;
#include <any>
#include <functional>
#include <span>
#include <vector>
export module engine:renderer;
import :shader;
import :renderable;

export namespace Engine {
    template<typename T>
    class Renderer {
    public:
        Renderer(const std::span<std::reference_wrapper<Shader>> &shaders_,
                 const std::vector<std::reference_wrapper<T>> &renderables_) :
            shaders(shaders_), renderables(renderables_){};
        virtual void render() const = 0;
        virtual ~Renderer() = default;

    protected:
        const std::span<std::reference_wrapper<Shader>> &shaders;
        std::vector<std::reference_wrapper<T>> renderables;
    };
} // namespace Engine
