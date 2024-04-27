module;
#include "GLFW/glfw3.h"
export module engine.renderable.terrain;
import engine.renderable;

export namespace Engine {
    class Text final: public Renderable {
    public:
        Text();
        void render() override;
        ~Text() override;
    private:
        unsigned width, height;
    };
}
