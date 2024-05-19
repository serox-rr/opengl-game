module;
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

export module engine:camera;

export namespace Engine {
    class Camera {
    public:
        explicit Camera(glm::vec3 position);

        glm::mat4 &getView();
        [[nodiscard]] float getPitch() const;
        [[nodiscard]] float getYaw() const;
        [[nodiscard]] float getSensitivity() const;
        [[nodiscard]] float getFov() const;
        [[nodiscard]] glm::vec3 getPosition() const;

        virtual void setLookingDirection(float yaw_, float pitch_) = 0;
        virtual void setPosition(glm::vec3 position_) = 0;
        void setFov(float _fov);
        void updateView();
        virtual ~Camera() = default;


    protected:
        glm::vec<3, double> position, front, up;
        glm::mat4 view;
        double yaw = -90.0, pitch = 0.0, sensitivity = 0.1, fov = 45.0;
    };
} // namespace Engine
