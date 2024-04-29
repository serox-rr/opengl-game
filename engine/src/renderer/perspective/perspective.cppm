module;
export module engine:renderer.perspective;
import :renderer;
import :camera;
export namespace Engine {
    class PerspectiveRenderer final : Renderer {
    public:
        explicit PerspectiveRenderer(Camera &camera_,
                                     const std::vector<std::reference_wrapper<Renderable>> &renderables_,
                                     const Shader &shader_);
        void render() override;

    private:
        Camera &camera;
    };
} // namespace Engine
