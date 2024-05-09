module;
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <span>

export module engine:entity;
import :renderable;
export namespace Engine {
    class Entity {
    public:
        Entity(glm::vec3 position_, double yaw_, double pitch_, double speed_, const std::initializer_list<std::reference_wrapper<const Renderable>> &collidables_);
        virtual void update() = 0;
        void setPosition(glm::vec3 position_);
        void setLookingDirection(float yaw_, float pitch_);
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
        virtual ~Entity() = default;
    protected:
        glm::vec3 position, front, up;
        float yaw, pitch, speed;
        std::vector<std::reference_wrapper<const Renderable>> collidables;
    };
} // namespace Engine
