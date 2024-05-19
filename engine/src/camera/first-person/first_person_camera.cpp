module;
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
module engine;
import :camera;

namespace Engine {
    FirstPersonCamera::FirstPersonCamera(const glm::vec3 &position_) : Camera(position_) {}

    void FirstPersonCamera::setLookingDirection(const float yaw_, const float pitch_) {
        yaw = yaw_;
        pitch = pitch_;
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch));
        front = glm::normalize(direction);
        updateView();
    }

    void FirstPersonCamera::setPosition(const glm::vec3 position_) {
        position = position_;
        updateView();
    }
} // namespace Engine
