module;
#include <glm/glm.hpp>
export module engine:camera.top_down;
import :camera;
export namespace Engine {
    class TopDownCamera final : public Camera {
    public:
        explicit TopDownCamera(const glm::vec3 &position_);
        ~TopDownCamera() override = default;
        void setLookingDirection(float yaw_, float pitch_) override;
    };
} // namespace Engine
