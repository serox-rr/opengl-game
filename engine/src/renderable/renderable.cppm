export module engine.renderable;

export namespace Engine {
    class Renderable {
    public:
        virtual void render() = 0;
        virtual ~Renderable() = default;
    };
}
