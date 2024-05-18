module;
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <memory>
export module engine:entity.player;
import :camera;
import :entity;

export namespace Engine {
    class Player final : public Entity {
    public:
        Player(const glm::vec3 &position_, double yaw_, double pitch_, double speed_, const std::initializer_list<std::reference_wrapper<const Renderable>> &collidables_, float mass_);
        void update() override;
        void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) const;
        void mouse_callback(GLFWwindow *window, double xpos, double ypos);
        void processInput(GLFWwindow *window);
        std::optional<bool> toggleInput(GLFWwindow *window, unsigned input);
        [[nodiscard]] Camera &getActiveCamera() const;
        ~Player() override = default;

    private:
        std::vector<std::shared_ptr<Camera>> cameras;
        std::shared_ptr<Camera> activeCamera;
        float lastMouseX, lastMouseY;
        bool firstMouse;
        std::map<unsigned, bool> keyStates;
    };
} // namespace Engine
