module;
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

export module engine:camera;

export namespace Engine {
    class Camera {
    public:
        explicit Camera(glm::vec3 position);

        glm::mat4 *getView();
        [[nodiscard]] float getPitch() const;
        [[nodiscard]] float getYaw() const;
        [[nodiscard]] float getSensitivity() const;
        [[nodiscard]] float getFov() const;
        [[nodiscard]] glm::vec3 getPosition() const;

        void moveRight();
        void moveLeft();
        void moveForward();
        void moveBackward();
        void moveUp();
        void moveDown();
        void setLookingDirection(float yaw, float pitch);
        void setSpeed(float _speed);
        void setPosition(glm::vec3 position);
        void addPosition(glm::vec3 position);
        void setFov(float _fov);
        void updateView();


    private:
        glm::vec3 position, front, up;
        glm::mat4 view;
        float yaw = -90.f, pitch = 0.0f, speed = 10.0f, sensitivity = 0.1f, fov = 45.0f;
    };
}
