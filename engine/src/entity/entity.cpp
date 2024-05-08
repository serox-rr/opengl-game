module;
#include <glm/glm.hpp>

module engine;

namespace Engine {
    Entity::Entity(const glm::vec3<double> &position_, const double yaw_, const double pitch_, const double speed_) :
        position(position_), front(glm::vec3(0.0, 0.0, -1.0)), up(glm::vec3(0.0, 1.0, 0.0)), yaw(yaw_), pitch(pitch_),
        speed(speed_) {}

    void Entity::setPosition(const glm::vec3 position_) { position = position_; }

    void Entity::setLookingDirection(float _yaw, float _pitch) {
        yaw = _yaw;
        pitch = _pitch;
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        front = glm::normalize(direction);
    }

    void Entity::addPosition(const glm::vec3 position_) { position += position_; }

    void Entity::moveRight() { addPosition(glm::normalize(glm::cross(front, up)) * speed); }

    void Entity::moveLeft() { addPosition(-glm::normalize(glm::cross(front, up)) * speed); }

    void Entity::moveForward() { addPosition(speed * front); }

    void Entity::moveBackward() { addPosition(-speed * front); }

    void Entity::moveUp() { addPosition(speed * up); }

    void Entity::moveDown() { addPosition(-speed * up); }

    void Entity::setSpeed(const float _speed) { speed = _speed; }

    float Entity::getPitch() const { return pitch; }

    float Entity::getYaw() const { return yaw; }

    glm::vec3 Entity::getPosition() const { return position; }
} // namespace Engine
