module;
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
module engine;

namespace Engine {
    Entity::Entity(glm::vec3 position_, double yaw_, double pitch_, double speed_,
                   const std::initializer_list<std::reference_wrapper<const Renderable>> &collidables_,
                   float mass_) :
        position(position_), front(0.0, 0.0, -1.0), up(0.0, 1.0, 0.0), force(0, 0, 0), uncontrolledVelocity(0, 0, 0),
        travelVelocity(0, 0, 0), yaw(yaw_), pitch(pitch_), speed(speed_), collidables(collidables_), mass(mass_) {}


    void Entity::setForce(const glm::vec3 force_) { force = force_; }

    void Entity::addForce(const glm::vec3 force_) { setForce(force + force_); }

    void Entity::setLookingDirection(const float yaw_, const float pitch_) {
        yaw = yaw_;
        pitch = pitch_;
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

    void Entity::setSpeed(const float _speed) { speed = _speed; }

    float Entity::getPitch() const { return pitch; }

    float Entity::getYaw() const { return yaw; }

    glm::vec3 Entity::getPosition() const { return position; }
} // namespace Engine
