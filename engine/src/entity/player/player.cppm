module;
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
export module engine:entity.player;
import :entity;

export namespace Engine {
    class Player : public Entity {
    public:
        Player(const glm::vec3 &position_, double yaw_, double pitch_, double speed_, Camera &camera_);
        void update() override;
        void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
        void mouse_callback(GLFWwindow *window, double xpos, double ypos);
        void processInput(GLFWwindow *window);

    private:
        Camera &camera;
        float lastMouseX, lastMouseY;
        bool firstMouse;
    };
} // namespace Engine
