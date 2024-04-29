module;
export module engine:renderable;
import :shader;

export namespace Engine {
    class Renderable {
    public:
        Renderable(const unsigned vao, const unsigned vbo):vao(vao),vbo(vbo) {};
        virtual void render() = 0;
        virtual ~Renderable() = default;
    protected:
        unsigned vao, vbo;
    };
}
