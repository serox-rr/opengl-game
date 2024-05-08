module;
#include <GLFW/glfw3.h>
#include <functional>
#include <glm/glm.hpp>
module engine;

namespace Engine {
    Player::Player(const glm::vec3 &position_, const double yaw_, const double pitch_, const double speed_,
                   Camera &camera_) :
        Entity(position_, yaw_, pitch_, speed_), camera(camera_), lastMouseX(windows[0].getWidth() / 2),
        lastMouseY(windows[0].getHeight() / 2), firstMouse(true) {
        processInput(windows[0]);
        static auto mouseCallbackStatic = [this](GLFWwindow *window, const double xpos, const double ypos) {
            mouse_callback(window, xpos, ypos);
        };
        static auto scrollCallbackStatic = [this](GLFWwindow *window, double xoffset, double yoffset) {
            scroll_callback(window, xoffset, yoffset);
        };
        glfwSetCursorPosCallback(windows[0], [](GLFWwindow *window, const double xpos, const double ypos) {
            mouseCallbackStatic(window, xpos, ypos);
        });
        glfwSetScrollCallback(windows[0], [](GLFWwindow *window, double xoffset, double yoffset) {
            scrollCallbackStatic(window, xoffset, yoffset);
        });
    }

    void Player::update() {
        camera.setPosition(position);
        camera.setLookingDirection(yaw, pitch);
    }

    void Player::processInput(GLFWwindow *window) {
        setSpeed(500.0f * deltaTime);
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            moveForward();
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            moveBackward();
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            moveLeft();
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            moveRight();
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            moveUp();
        if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
            moveDown();
    }


    void Player::mouse_callback(GLFWwindow *window, const double xpos, const double ypos) {
        float xoffset = xpos - lastMouseX;
        float yoffset = lastMouseY - ypos; // reversed since y-coordinates range from bottom to top
        lastMouseX = xpos;
        lastMouseY = ypos;
        if (firstMouse) // initially set to true
        {
            lastMouseX = xpos;
            lastMouseY = ypos;
            firstMouse = false;
        }
        xoffset *= camera.getSensitivity();
        yoffset *= camera.getSensitivity();
        setLookingDirection(yaw + xoffset, pitch + yoffset);
    }

    void Player::scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
        camera.setFov(camera.getFov() - static_cast<float>(yoffset));
    }

} // namespace Engine
