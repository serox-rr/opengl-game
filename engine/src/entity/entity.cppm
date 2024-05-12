module;
#include <any>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <span>

export module engine:entity;
import :renderable;
export namespace Engine {
    class Entity {
    public:
        Entity(glm::vec3 position_, double yaw_, double pitch_, double speed_, const std::initializer_list<std::reference_wrapper<const Renderable>> &collidables_, float mass_);
        virtual void update() = 0;
        void setForce(glm::vec3 force_);
        void setLookingDirection(float yaw_, float pitch_);
        void addForce(glm::vec3 force_);
        void setSpeed(float _speed);
        [[nodiscard]] float getPitch() const;
        [[nodiscard]] float getYaw() const;
        [[nodiscard]] glm::vec3 getPosition() const;
        virtual ~Entity() = default;
    protected:
        glm::vec3 position, front, up, uncontrolledVelocity, force, travelVelocity;
        float yaw, pitch, mass, speed;
        std::vector<std::reference_wrapper<const Renderable>> collidables;
    };
} // namespace Engine
