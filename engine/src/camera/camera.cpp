module;
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
module engine;

namespace Engine {
    Camera::Camera(const glm::vec3 _position): position(_position), front(glm::vec3(0.0, 0.0, -1.0)), up( glm::vec3(0.0, 1.0,  0.0)), view(glm::lookAt(position, position + front, up)) {}

    glm::mat4 &Camera::getView() {
        return view;
    }

    void Camera::updateView() {
        view = glm::lookAt(position, position + front, up);
    }

    float Camera::getPitch() const {
        return pitch;
    }

    float Camera::getYaw() const {
        return yaw;
    }

    float Camera::getSensitivity() const {
        return sensitivity;
    }

    float Camera::getFov() const {
        return fov;
    }

    void Camera::setFov(float _fov) {
        fov = _fov;
        if (fov < 1.0f)
            fov = 1.0f;
        if (fov > 180.0f)
            fov = 180.0f;
    }

    glm::vec3 Camera::getPosition() const {
        return position;
    }
}
