module;
#include "GLFW/glfw3.h"
export module engine.renderable.terrain;
import engine.renderable;

export namespace Engine {
    class Terrain final: public Renderable {
    public:
        Terrain();
        void render() override;
        ~Terrain() override;
    private:
        GLuint vao;
        unsigned width, height;
    };
}
