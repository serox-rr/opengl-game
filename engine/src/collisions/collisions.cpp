module;
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
module engine;

namespace Engine::Collisions {
    glm::vec3 check(const Entity *entity, const std::vector<std::reference_wrapper<const Renderable>> &renderables,
                    const glm::vec3 &position) {
        if (const auto terrain = dynamic_cast<const Terrain *>(&renderables[0].get())) {
            const auto &heightMap = terrain->getHeightMap();
            const auto width = terrain->getWidth();
            const auto height = terrain->getHeight();
            const auto x = static_cast<int>(position.x) + width / 2;
            const auto z = static_cast<int>(position.z) + height / 2;
            if (x > width || z > height || x < 0 || z < 0)
                return position;

            if (const double y = heightMap.at(z * width + x) * 64.0 + 1; y > position.y)
                return glm::vec3(position.x, y, position.z);
        }
        return position;
    }
} // namespace Engine::Collisions
