module;
#include <glm/glm.hpp>
export module engine:camera.first_person;

import :camera;

export namespace Engine {
    class FirstPersonCamera final :public Camera {
    public:
        explicit FirstPersonCamera(const glm::vec3 &position_);
        void setLookingDirection(float yaw_, float pitch_) override;
        ~FirstPersonCamera() override = default;
    };
} // namespace Engine
