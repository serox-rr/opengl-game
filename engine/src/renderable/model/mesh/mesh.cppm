module;
#include <vector>
export module engine:renderable.mesh;
import :renderable;

export namespace Engine {
    class Mesh final: public Renderable {
    public:
        Mesh(const std::vector<Vertex> &vertices_, const std::vector<unsigned int> &indices_, const std::vector<ModelTexture> &textures_, Shader &shader);
        [[nodiscard]] std::vector<Vertex> getVertices() const { return vertices; }
        void render() const override;
    private:
        const std::vector<unsigned int> indices;
        const std::vector<ModelTexture>      textures;
        unsigned ebo;
        std::vector<Vertex> vertices;
    };
}
