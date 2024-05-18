module;
export module engine:renderer.model;
import :renderer;
import :camera;
import :renderable.model;
import :entity.player;
export namespace Engine {
    class ModelRenderer final : Renderer<Model> {
    public:
        explicit ModelRenderer(Player &player_, const std::vector<std::reference_wrapper<Model>> &models_,
                               const std::span<std::reference_wrapper<Shader>> &shaders_);
        void render() const override;

    private:
        Player &player;
    };
} // namespace Engine
