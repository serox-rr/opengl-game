module;
export module engine:renderer.perspective;
import :renderer;
import :camera;
import :entity.player;
export namespace Engine {
    class PerspectiveRenderer final : Renderer<Renderable> {
    public:
        explicit PerspectiveRenderer(Player &player_,
                                     const std::vector<std::reference_wrapper<Renderable>> &renderables_,
                                     const std::span<std::reference_wrapper<Shader>> &shaders_);
        void render() const override;

    private:
        Player &player;
    };
} // namespace Engine
