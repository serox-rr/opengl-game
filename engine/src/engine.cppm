module;
#include <vector>
export module engine;
export import :camera;
export import :shader;
export import :texture;
export import :window;

export namespace Engine {
    void init();
    void settings();
    void initFreeType();
    std::vector<Shader> shaders{};
}
