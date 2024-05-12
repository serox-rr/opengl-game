module;
export module engine:renderer.perspective;
import :renderer;
import :camera;
export namespace Engine {
    class PerspectiveRenderer final : Renderer<Renderable> {
    public:
        explicit PerspectiveRenderer(Camera &camera_,
                                     const std::vector<std::reference_wrapper<Renderable>> &renderables_,
                                     const std::span<std::reference_wrapper<Shader>> &shaders_);
        void render() const override;

    private:
        Camera &camera;
    };
} // namespace Engine
