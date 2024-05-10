module;
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
export module engine:physics.collisions;
import :renderable;
import :entity;

export namespace Engine::Physics {
    std::optional<glm::vec3> checkCollision(const Entity *entity, const std::vector<std::reference_wrapper<const Renderable>> &renderables,
                    const glm::vec3 &position);
} // namespace Engine::Collisions
