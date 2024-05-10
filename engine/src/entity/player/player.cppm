module;
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
export module engine:entity.player;
import :camera;
import :entity;

export namespace Engine {
    class Player final : public Entity {
    public:
        Player(const glm::vec3 &position_, double yaw_, double pitch_, double speed_, Camera &camera_, const std::initializer_list<std::reference_wrapper<const Renderable>> &collidables_, float mass_);
        void update() override;
        void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
        void mouse_callback(GLFWwindow *window, double xpos, double ypos);
        void processInput(GLFWwindow *window);
        std::optional<bool> toggleInput(GLFWwindow *window, unsigned input);
        ~Player() override = default;

    private:
        Camera &camera;
        float lastMouseX, lastMouseY;
        bool firstMouse;
        std::map<unsigned, bool> keyStates;
    };
} // namespace Engine
