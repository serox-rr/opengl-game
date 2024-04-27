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
        glm::vec<3, double> position, front, up;
        glm::mat4 view;
        double yaw = -90.0, pitch = 0.0, speed = 10.0, sensitivity = 0.1, fov = 45.0;
    };
}
