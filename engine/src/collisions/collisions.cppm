module;
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
export module engine:collisions;
import :renderable;
import :entity;

export namespace Engine::Collisions {
    glm::vec3 check(const Entity *entity, const std::vector<std::reference_wrapper<const Renderable>> &renderables,
                    const glm::vec3 &position);
} // namespace Engine::Collisions
