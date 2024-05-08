module;
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

export module engine:entity;
import :collisions;
export namespace Engine {
    class Entity {
    public:
        Entity(glm::vec3 position_, double yaw_, double pitch_, double speed_);
        virtual void update() = 0;
        void setPosition(glm::vec3 position_);
        void setLookingDirection(float yaw, float pitch);
        void addPosition(glm::vec3 position_);
        void setSpeed(float _speed);
        void moveRight();
        void moveLeft();
        void moveForward();
        void moveBackward();
        void moveUp();
        void moveDown();
        [[nodiscard]] float getPitch() const;
        [[nodiscard]] float getYaw() const;
        [[nodiscard]] glm::vec3 getPosition() const;

    protected:
        glm::vec<3, double> position, front, up;
        double yaw, pitch, speed;
    };
} // namespace Engine
