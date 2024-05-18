module;
#include <GLFW/glfw3.h>
#include <functional>
#include <glm/glm.hpp>
#include <iostream>
#include <optional>
module engine;

namespace Engine {
    Player::Player(const glm::vec3 &position_, double yaw_, double pitch_, double speed_,
                   const std::initializer_list<std::reference_wrapper<const Renderable>> &collidables_,
                   const float mass_) :
        Entity(position_, yaw_, pitch_, speed_, collidables_, mass_), lastMouseX(windows[0].getWidth() / 2),
        lastMouseY(windows[0].getHeight() / 2), firstMouse(true), keyStates({{GLFW_KEY_V, false}, {GLFW_KEY_SPACE, false}}) {
        cameras.emplace_back(std::make_shared<FirstPersonCamera>(position_));
        cameras.emplace_back(std::make_shared<TopDownCamera>(position_));
        activeCamera = cameras[0];
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
        addForce(glm::vec3(0, -9.81f, 0));
    }

    void Player::update() {
        uncontrolledVelocity += force * deltaTime;
        auto tposition = (uncontrolledVelocity + travelVelocity) * deltaTime + position;
        if (const auto colY = Physics::checkCollision(this, collidables, tposition); colY.has_value()) {
            tposition = colY.value();
            uncontrolledVelocity.y = 0;
        }
        position = tposition;
        activeCamera->setPosition(position);
        activeCamera->setLookingDirection(yaw, pitch);
    }

    std::optional<bool> Player::toggleInput(GLFWwindow *window, const unsigned input) {
        if (glfwGetKey(window, input) == GLFW_PRESS && !keyStates[input])
            return keyStates[input] = true;
        if (glfwGetKey(window, input) == GLFW_RELEASE && keyStates[input])
            return keyStates[input] = false;
        return std::nullopt;
    }

    void Player::processInput(GLFWwindow *window) {
        travelVelocity = glm::vec3(0, 0, 0);
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            travelVelocity += glm::vec3(1, 0, 1) * speed * front;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            travelVelocity -= glm::vec3(1, 0, 1) * speed * front;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            travelVelocity -= glm::vec3(1, 0, 1) * speed * glm::normalize(glm::cross(front, up));
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            travelVelocity += glm::vec3(1, 0, 1) * speed * glm::normalize(glm::cross(front, up));
        if (const auto key = toggleInput(window, GLFW_KEY_SPACE);
            key.has_value() && key.value() && uncontrolledVelocity.y == 0)
            uncontrolledVelocity.y += 10;
        if (const auto key = toggleInput(window, GLFW_KEY_V); key.has_value() && key.value()) {
            activeCamera = cameras[cameras[0] == activeCamera];
        }
        setSpeed(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ? 500 : 3.5);
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
        xoffset *= activeCamera->getSensitivity();
        yoffset *= activeCamera->getSensitivity();
        setLookingDirection(yaw + xoffset, pitch + yoffset);
    }

    void Player::scroll_callback(GLFWwindow *window, double xoffset, double yoffset) const {
        activeCamera->setFov(activeCamera->getFov() - static_cast<float>(yoffset));
    }

    Camera &Player::getActiveCamera() const { return *activeCamera; }
} // namespace Engine
