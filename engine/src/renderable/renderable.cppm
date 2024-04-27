module;
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
export module engine.renderable;

export namespace Engine {
    class Renderable {
    public:
        virtual void render() = 0;
        virtual ~Renderable() = default;
    protected:
        GLuint vao{};
        glm::vec3 position{};
    };
}
