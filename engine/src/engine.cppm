module;

export module engine;
export import :utils;
export import :camera;
export import :shader;
export import :texture;
export import :window;
export import :font;
export import :exception;
export import :renderer;
export import :renderer.perspective;
export import :renderable;
export import :renderable.terrain;
export import :renderable.text;
export import :renderable.light;
export import :renderable.vectors;
export import :entity;

export namespace Engine {
    void init();
    void settings();

    std::vector<Window> windows({});
}
